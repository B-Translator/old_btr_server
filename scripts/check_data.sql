
--use en;
use sq;
--use de;
--use fr;
--use it;
--use es;

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
