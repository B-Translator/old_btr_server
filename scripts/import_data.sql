
use l10nsq;

----------------------------------------------------------
-- Import the phrases
----------------------------------------------------------

/**
 * We use an auxiliary column to keep the old id,
 * which will help us to recreate the relations.
 */
alter table l10n_suggestions_strings add column old_id int;

/**
 * The column hash will be used for more efficient and reliable
 * text comparison.
 * hash = sha1(trim(string))
 */
--alter table l10n_suggestions_strings add column hash varchar(40) after string;

/**
 * Importing bulk data is done a bit faster if keys and indexes
 * are droped before the import and recreated after it.
 */
alter table l10n_suggestions_strings drop key hash;
alter table l10n_suggestions_strings drop index string;
alter table l10n_suggestions_strings drop index string_text;

insert into l10n_suggestions_strings (string, hash, length, old_id)
select phrase, hash, length, id from en.phrases;

--select * from l10n_suggestions_strings limit 10;
--select count(*) from l10n_suggestions_strings;  --417590
--select count(*) from en.phrases;  --417590

alter table l10n_suggestions_strings add unique key hash (hash);
alter table l10n_suggestions_strings add index string (string(100));
alter table l10n_suggestions_strings add fulltext index string_text (string);

/** we need to add an index on old_id, in order to make
some later operations more efficient */
alter table l10n_suggestions_strings add unique key old_id (old_id);


----------------------------------------------------------
-- Import the locations
----------------------------------------------------------

/**
 * We use an auxiliary column to keep the old id,
 * which will help us to recreate the relations.
 */
alter table l10n_suggestions_locations add column old_phraseid int;

/**
 * Importing bulk data is done a bit faster if keys and indexes
 * are droped before the import and recreated after it.
 */
alter table l10n_suggestions_locations drop index projectname;

insert into l10n_suggestions_locations (old_phraseid, projectname, flags)
select phraseid, project, flags from en.locations;

--select * from l10n_suggestions_locations limit 10;
--select count(*) from l10n_suggestions_locations;  --1149985
--select count(*) from en.locations;  --1149985

/** fix the reference id to the phrase */
update l10n_suggestions_locations l
set l.sid = (select s.sid from l10n_suggestions_strings s
             where s.old_id = l.old_phraseid);

/** recreate indexes */
alter table l10n_suggestions_locations add index projectname (projectname(5));

/** we don't need column old_phraseid any more */
alter table l10n_suggestions_locations drop column old_phraseid;


/** drop the column old_id of strings */
alter table l10n_suggestions_strings drop key old_id;
alter table l10n_suggestions_strings drop column old_id;
