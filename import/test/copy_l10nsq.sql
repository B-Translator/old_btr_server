use l10nsq;

truncate table l10n_suggestions_files;
truncate table l10n_suggestions_projects;
truncate table l10n_suggestions_locations;
truncate table l10n_suggestions_strings;
truncate table l10n_suggestions_translations;
truncate table l10n_suggestions_votes;
truncate table l10n_suggestions_users;

alter table l10n_suggestions_files disable keys;
insert into l10n_suggestions_files select * from l10nsq_test.l10n_suggestions_files;
alter table l10n_suggestions_files enable keys;

alter table l10n_suggestions_projects disable keys;
insert into l10n_suggestions_projects select * from l10nsq_test.l10n_suggestions_projects;
alter table l10n_suggestions_projects enable keys;

alter table l10n_suggestions_locations disable keys;
insert into l10n_suggestions_locations select * from l10nsq_test.l10n_suggestions_locations;
alter table l10n_suggestions_locations enable keys;

alter table l10n_suggestions_strings disable keys;
insert into l10n_suggestions_strings select * from l10nsq_test.l10n_suggestions_strings;
alter table l10n_suggestions_strings enable keys;

alter table l10n_suggestions_translations disable keys;
insert into l10n_suggestions_translations select * from l10nsq_test.l10n_suggestions_translations;
alter table l10n_suggestions_translations enable keys;

alter table l10n_suggestions_votes disable keys;
insert into l10n_suggestions_votes select * from l10nsq_test.l10n_suggestions_votes;
alter table l10n_suggestions_votes enable keys;

alter table l10n_suggestions_users disable keys;
insert into l10n_suggestions_users select * from l10nsq_test.l10n_suggestions_users;
alter table l10n_suggestions_users enable keys;

