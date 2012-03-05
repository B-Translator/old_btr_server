use l10nsq;

truncate table l10n_feedback_files;
truncate table l10n_feedback_projects;
truncate table l10n_feedback_locations;
truncate table l10n_feedback_strings;
truncate table l10n_feedback_translations;
truncate table l10n_feedback_votes;
truncate table l10n_feedback_users;

alter table l10n_feedback_files disable keys;
insert into l10n_feedback_files select * from l10nsq_test.l10n_feedback_files;
alter table l10n_feedback_files enable keys;

alter table l10n_feedback_projects disable keys;
insert into l10n_feedback_projects select * from l10nsq_test.l10n_feedback_projects;
alter table l10n_feedback_projects enable keys;

alter table l10n_feedback_locations disable keys;
insert into l10n_feedback_locations select * from l10nsq_test.l10n_feedback_locations;
alter table l10n_feedback_locations enable keys;

alter table l10n_feedback_strings disable keys;
insert into l10n_feedback_strings select * from l10nsq_test.l10n_feedback_strings;
alter table l10n_feedback_strings enable keys;

alter table l10n_feedback_translations disable keys;
insert into l10n_feedback_translations select * from l10nsq_test.l10n_feedback_translations;
alter table l10n_feedback_translations enable keys;

alter table l10n_feedback_votes disable keys;
insert into l10n_feedback_votes select * from l10nsq_test.l10n_feedback_votes;
alter table l10n_feedback_votes enable keys;

alter table l10n_feedback_users disable keys;
insert into l10n_feedback_users select * from l10nsq_test.l10n_feedback_users;
alter table l10n_feedback_users enable keys;

