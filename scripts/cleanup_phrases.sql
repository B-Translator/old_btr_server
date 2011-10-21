/**
 * Leading and trailing spaces in a phrase make them
 * look like different phrases, when actually they are
 * the same. We are going to normalize phrases by trimming
 * all the leading and trailing spaces.
 *
 * This may break the uniqueness of the phrases and
 * we should remove the doublicates.
 * However, before doing this, we should replace the
 * phraseid of the phrases that are going to be removed
 * with the phraseid of the remaining phrase (which is
 * the same as the removed phrases), on the other tables
 * (locations.phraseid and wp.phraseid).
 */

--use en;
use sq;
--use de;
--use fr;
--use it;
--use es;
 
/** trim column phrase */
update phrases set phrase = trim(phrase);
/** create an index on column hash for more efficient processing */
create index hash on phrases (hash);

/** 
 * Create a table phrase_1 that contains the phrases 
 * that occour more than once on phrase.
 */
drop table if exists phrases_1;
create table phrases_1 like phrases;
insert into phrases_1
(select * from phrases group by hash having count(*) > 1);
--select * from phrases_1 limit 10;
--select count(*) from phrases_1;

/** add a second id column to table phrases */
alter table phrases add column (id_2 int);
--select * from phrases limit 10;

/**
 * On the second id column store the unique id of each phrase.
 * For phrases with multiple occourencies this unique id can
 * be taken from table phrase_1. For the rest of the phrases
 * it is the same as the id.
 */
update phrases
set id_2 = (select id from phrases_1 where phrases_1.hash = phrases.hash);

update phrases 
set id_2 = id
where id_2 is null;

/** we don't need table phrases_1 anymore */
drop table phrases_1;


/**
 * replace each phraseid on table locations 
 * with the unique id of the phrase
 */
update locations
set phraseid = (select id_2 from phrases where phrases.id = locations.phraseid);
--select count(*) from locations where phraseid is null;
--delete from from locations where phraseid is null;

/**
 * replace each phraseid on table wp 
 * with the unique id of the phrase
 */
update wp
set phraseid = (select id_2 from phrases where phrases.id = wp.phraseid);
--select count(*) from wp where phraseid is null;
--delete from from wp where phraseid is null;

/** remove from table phrases extra occurencies */
--select count(*) from phrases where id != id_2;
delete from phrases where id != id_2;

/** we don't need column id_2 anymore */
alter table phrases drop column id_2;
