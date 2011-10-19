
/** collate utf8_bin makes the column word case sensitive */
alter table en.words modify column word varchar(1000) collate utf8_bin;

/** remove the spaces at the beginning and end, just in case */
update en.words set word = trim(word);

/** check for doublicate words */
select *, count(*) from en.words 
group by word having count(*) > 1
order by count(*) desc;

/**
 * text comparisons are not efficient and reliable in mysql,
 * so, we use a hash value of the trimmed phrase in order to
 * make comparisons and to ensure uniqueness of the phrases
 */
alter table en.phrases add column hash binary(20);
update en.phrases set hash = unhex(sha1(trim(phrase)));
--select * from en.phrases limit 10;

/** check for doublicate phrases */
select *, count(*) from en.phrases 
group by hash having count(*) > 1
order by count(*) desc;

-- run the script cleanup_phrases.sql
-- to fix doublicate phrases

/**
 * check the table wp for dangling relationships and clean them
 */
select * from en.phrases p
right join en.wp wp on (wp.phraseid = p.id)
where p.id is null;

drop table if exists en.wp_1;
create table en.wp_1 like en.wp;

insert into en.wp_1
  (select wp.* from en.phrases p
   right join en.wp wp on (wp.phraseid = p.id)
   where p.id is null);
--select * from en.wp_1;

delete from en.wp where phraseid in (select wp1.phraseid from en.wp_1 wp1);
drop table en.wp_1;

select * from en.words w
right join en.wp wp on (wp.wordid = w.id)
where w.id is null;

drop table if exists en.wp_1;
create table en.wp_1 like en.wp;
insert into en.wp_1
  (select wp.* from en.words w
   right join en.wp wp on (wp.wordid = w.id)
   where w.id is null);
--select * from en.wp_1;
delete from en.wp where wordid in (select wp1.wordid from en.wp_1 wp1);
drop table en.wp_1;

