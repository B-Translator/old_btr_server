use l10nsq_test;

drop table if exists l10n_feedback_files;
drop table if exists l10n_feedback_projects;
drop table if exists l10n_feedback_locations;
drop table if exists l10n_feedback_strings;
drop table if exists l10n_feedback_translations;
drop table if exists l10n_feedback_votes;
drop table if exists l10n_feedback_users;

create table l10n_feedback_files like l10nsq.l10n_feedback_files;
create table l10n_feedback_projects like l10nsq.l10n_feedback_projects;
create table l10n_feedback_locations like l10nsq.l10n_feedback_locations;
create table l10n_feedback_strings like l10nsq.l10n_feedback_strings;
create table l10n_feedback_translations like l10nsq.l10n_feedback_translations;
create table l10n_feedback_votes like l10nsq.l10n_feedback_votes;
create table l10n_feedback_users like l10nsq.l10n_feedback_users;
