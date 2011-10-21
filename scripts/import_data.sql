
use l10nsq;

----------------------------------------------------------
-- Import the phrases
----------------------------------------------------------

/**
 * We use an auxiliary column to keep the old id, 
 * which will help us to recreate the relations.
 */
alter table l10n_suggestions_phrases add column old_id int;

/**
 * The column hash will be used for more efficient and reliable
 * text comparison.
 * hash = unhex(sha1(trim(phrase)))
 */
--alter table l10n_suggestions_phrases add column hash binary(20) after phrase;

/**
 * Importing bulk data is done a bit faster if keys and indexes
 * are droped before the import and recreated after it.
 */
alter table l10n_suggestions_phrases drop key hash;
alter table l10n_suggestions_phrases drop index phrase;

insert into l10n_suggestions_phrases (phrase, hash, length, old_id)
select phrase, hash, length, id from en.phrases;

--select * from l10n_suggestions_phrases limit 10;
--select count(*) from l10n_suggestions_phrases;  --417590
--select count(*) from en.phrases;  --417590

alter table l10n_suggestions_phrases add unique key hash (hash);
alter table l10n_suggestions_phrases add index phrase (phrase(100));

/** we need to add an index on old_id, in order to make 
some later operations more efficient */
alter table l10n_suggestions_phrases add unique key old_id (old_id);


----------------------------------------------------------
-- Import the words
----------------------------------------------------------

--select max(length(word)) from en.words;  --49

/**
 * We use an auxiliary column to keep the old id, 
 * which will help us to recreate the relations.
 */
alter table l10n_suggestions_words add column old_id int;

/**
 * Importing bulk data is done a bit faster if keys and indexes
 * are droped before the import and recreated after it.
 */
alter table l10n_suggestions_words drop key word;

insert into l10n_suggestions_words (word, old_id)
select word, id from en.words;

--select * from l10n_suggestions_words limit 10;
--select count(*) from l10n_suggestions_words;  --53340
--select count(*) from en.words;  --53340

alter table l10n_suggestions_words add unique key word (word(100));

/** we need to add an index on old_id, in order to make 
some later operations more efficient */
alter table l10n_suggestions_words add unique key old_id (old_id);


----------------------------------------------------------
-- Import the locations
----------------------------------------------------------

/**
 * We use an auxiliary column to keep the old id, 
 * which will help us to recreate the relations.
 */
alter table l10n_suggestions_locations add column old_phraseid int;

insert into l10n_suggestions_locations (old_phraseid, projectname, flags)
select phraseid, project, flags from en.locations;

--select * from l10n_suggestions_locations limit 10;
--select count(*) from l10n_suggestions_locations;  --1149985
--select count(*) from en.locations;  --1149985

/** fix the reference id to the phrase */
update l10n_suggestions_locations l
set l.pid = (select p.pid from l10n_suggestions_phrases p 
             where p.old_id = l.old_phraseid);

/** we don't need column old_phraseid any more */
alter table l10n_suggestions_locations drop column old_phraseid;


----------------------------------------------------------
-- Import the word-phrases
----------------------------------------------------------

/**
 * We use auxiliary columns to keep the old ids, 
 * which will help us to recreate the relations.
 */
alter table l10n_suggestions_wordphrases add column old_wid int;
alter table l10n_suggestions_wordphrases add column old_pid int;

/** the primary key constraint prevents the import */
alter table l10n_suggestions_wordphrases drop primary key;

insert into l10n_suggestions_wordphrases (old_wid, old_pid, count)
select wordid, phraseid, count from en.wp;

--select * from l10n_suggestions_wordphrases limit 10;
--select count(*) from l10n_suggestions_wordphrases;  --1924176
--select count(*) from en.wp;  --1924176

/** fix the reference ids to the words */
update l10n_suggestions_wordphrases wp
set wp.wid = (select w.wid from l10n_suggestions_words w 
             where w.old_id = wp.old_wid);

/** fix the reference ids to the phrases */
update l10n_suggestions_wordphrases wp
set wp.pid = (select p.pid from l10n_suggestions_phrases p 
             where p.old_id = wp.old_pid);

/** we don't need columns old_wid and old_pid anymore */
alter table l10n_suggestions_wordphrases drop column old_wid;
alter table l10n_suggestions_wordphrases drop column old_pid;

/** let's create a primary key on (wid,pid) */
alter table l10n_suggestions_wordphrases add primary key wordphrase (wid,pid);

/** drop the columns old_id of words and phrases */
alter table l10n_suggestions_phrases drop key old_id;
alter table l10n_suggestions_phrases drop column old_id;
alter table l10n_suggestions_words drop key old_id;
alter table l10n_suggestions_words drop column old_id;

