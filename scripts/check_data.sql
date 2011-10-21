
--use en;
use sq;
--use de;
--use fr;
--use it;
--use es;

/** collate utf8_bin makes the column word case sensitive */
alter table words modify column word varchar(100) collate utf8_bin;

/** remove the spaces at the beginning and end, just in case */
update words set word = trim(word);

/** check for doublicate words */
select *, count(*) from words 
group by word having count(*) > 1
order by count(*) desc;

/**
 * text comparisons are not efficient and reliable in mysql,
 * so, we use a hash value of the trimmed phrase in order to
 * make comparisons and to ensure uniqueness of the phrases
 */
alter table phrases add column hash binary(20);
update phrases set hash = unhex(sha1(trim(phrase)));
--select * from phrases limit 10;

/** check for doublicate phrases */
select *, count(*) from phrases 
group by hash having count(*) > 1
order by count(*) desc;

-- run the script cleanup_phrases.sql
-- to fix doublicate phrases

/**
 * check the table wp for dangling relationships and clean them
 */
select * from phrases
right join wp on (wp.phraseid = phrases.id)
where phrases.id is null;

drop table if exists wp_1;
create table wp_1 like wp;

insert into wp_1
  (select wp.* from phrases
   right join wp on (wp.phraseid = phrases.id)
   where phrases.id is null);
--select * from wp_1;

delete from wp where phraseid in (select phraseid from wp_1);
drop table wp_1;

select * from words
right join wp on (wp.wordid = words.id)
where words.id is null;

drop table if exists wp_1;
create table wp_1 like wp;
insert into wp_1
  (select wp.* from words
   right join wp on (wp.wordid = words.id)
   where words.id is null);
--select * from wp_1;
delete from wp where wordid in (select wordid from wp_1);
drop table wp_1;

/** check the table wp for douplicate (phraseid,wordid) records */
select *, count(*) from wp
group by wordid, phraseid 
having count(*) > 1;

/** clean the table wp from douplicate (phraseid,wordid) records */
drop table if exists wp_1;
create table wp_1 like wp;
insert into wp_1 select * from wp group by wordid, phraseid;
drop table wp;
rename table wp_1 to wp;
