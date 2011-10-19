/**
 * Leading and trailing spaces in a phrase make them
 * look like different phrases, when actually they are
 * the same. We are going to normalize phrases by trimming
 * all the leading and trailing spaces.
 *
 * This will break the uniqueness of the phrases and
 * we should remove the doublicates.
 * However, before doing this, we should replace the
 * phraseid of the phrases that are going to be removed
 * with the phraseid of the remaining phrase (which is
 * the same as the removed phrases), on the other tables
 * (locations.phraseid and wp.phraseid).
 */

/** trim column phrase */
update en.phrases set phrase = trim(phrase);
/** create an index on column hash for more efficient processing */
create index phrase_hash on en.phrases (hash);

/** 
 * Create a table phrase_1 that contains the phrases 
 * that occour more than once on phrase.
 */
drop table if exists en.phrases_1;
create table en.phrases_1 like en.phrases;
insert into en.phrases_1
(select * from en.phrases group by hash having count(*) > 1);
--select * from en.phrases_1 limit 10;
--select count(*) from en.phrases_1;

/** add a second id column to table phrases */
alter table en.phrases add column (id_2 int);
--select * from en.phrases limit 10;

/**
 * On the second id column store the unique id of each phrase.
 * For phrases with multiple occourencies this unique id can
 * be taken from table phrase_1. For the rest of the phrases
 * it is the same as the id.
 */
update en.phrases p
set id_2 = (select id from en.phrases_1 p1 where p1.hash = p.hash);

update en.phrases p
set id_2 = id
where id_2 is null;

/** we don't need table phrases_1 anymore */
drop table en.phrases_1;


/**
 * replace each phraseid on table locations 
 * with the unique id of the phrase
 */
update en.locations l
set phraseid = (select id_2 from en.phrases p where p.id = l.phraseid);
--select count(*) from en.locations where phraseid is null;
--delete from from en.locations where phraseid is null;

/**
 * replace each phraseid on table wp 
 * with the unique id of the phrase
 */
update en.wp w
set phraseid = (select id_2 from en.phrases p where p.id = w.phraseid);
--select count(*) from en.wp where phraseid is null;
--delete from from en.wp where phraseid is null;

/** remove from table phrases extra occurencies */
--select count(*) from en.phrases where id != id_2;
delete from en.phrases where id != id_2;

/** we don't need column id_2 anymore */
alter table en.phrases drop column id_2;
