<?php
/**
 * @file
 * btr_janrain.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btr_janrain_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_accounts_string';
  $strongarm->value = 'Linked accounts';
  $export['rpx_accounts_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_login_form';
  $strongarm->value = 1;
  $export['rpx_attach_login_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_comments_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_comments_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_nodecont_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_nodecont_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_nodecont_weight_simplenews';
  $strongarm->value = '40';
  $export['rpx_attach_share_link_to_nodecont_weight_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_nodelink_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_nodelink_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_attach_share_link_to_teasers_simplenews';
  $strongarm->value = 0;
  $export['rpx_attach_share_link_to_teasers_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_bypass_email_verification';
  $strongarm->value = 0;
  $export['rpx_bypass_email_verification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_comment_popup_social_at_once_simplenews';
  $strongarm->value = 0;
  $export['rpx_comment_popup_social_at_once_simplenews'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_label_comments';
  $strongarm->value = 'Share your comment:';
  $export['rpx_default_label_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_label_nodes';
  $strongarm->value = 'Comment:';
  $export['rpx_default_label_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_linktext_comments';
  $strongarm->value = '[comment:subject]';
  $export['rpx_default_linktext_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_linktext_nodes';
  $strongarm->value = '[node:title]';
  $export['rpx_default_linktext_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_message_comments';
  $strongarm->value = 'Commented on [site:name].';
  $export['rpx_default_message_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_message_nodes';
  $strongarm->value = 'Shared [node:title] on [site:name].';
  $export['rpx_default_message_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_summary_comments';
  $strongarm->value = '[comment:body]';
  $export['rpx_default_summary_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_summary_nodes';
  $strongarm->value = '[node:body]';
  $export['rpx_default_summary_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_title_comments';
  $strongarm->value = '[node:title] | [site:name]';
  $export['rpx_default_title_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_default_title_nodes';
  $strongarm->value = '[node:title] | [site:name]';
  $export['rpx_default_title_nodes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_enabled_providers';
  $strongarm->value = array(
    0 => 'google',
    1 => 'facebook',
    2 => 'twitter',
    3 => 'linkedin',
    4 => 'paypal',
  );
  $export['rpx_enabled_providers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_extended_authinfo';
  $strongarm->value = 0;
  $export['rpx_extended_authinfo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_force_registration_form';
  $strongarm->value = 1;
  $export['rpx_force_registration_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_import_profile_photo';
  $strongarm->value = 1;
  $export['rpx_import_profile_photo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_javascript_global';
  $strongarm->value = 1;
  $export['rpx_javascript_global'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_login_icons_size';
  $strongarm->value = 'medium';
  $export['rpx_login_icons_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_login_links_weight';
  $strongarm->value = '-150';
  $export['rpx_login_links_weight'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_mail_rpx_confirm_email_body';
  $strongarm->value = '[user:name],

Thank you for registering at [site:name].

To confirm your email address, click on this link or copy and paste it in your browser:

[user:one-time-login-url]

After confirming your email address, you will be able to log in to [site:name] using your new account.

--  [site:name] team';
  $export['rpx_mail_rpx_confirm_email_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_mail_rpx_confirm_email_subject';
  $strongarm->value = 'Confirm your account at [site:name]';
  $export['rpx_mail_rpx_confirm_email_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_mapping_api';
  $strongarm->value = 0;
  $export['rpx_mapping_api'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_openid_override';
  $strongarm->value = 1;
  $export['rpx_openid_override'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_realm_scheme';
  $strongarm->value = 'https';
  $export['rpx_realm_scheme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_signin_string';
  $strongarm->value = 'Sign in with one of these:';
  $export['rpx_signin_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_social_enabled';
  $strongarm->value = 1;
  $export['rpx_social_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_social_pub';
  $strongarm->value = '';
  $export['rpx_social_pub'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rpx_user_help_text';
  $strongarm->value = '<p>This site supports <a href="http://www.janrain.com/products/engage/">Janrain Engage</a>, an easy way to log in to many websites using your account with Facebook, Google, Yahoo!, Twitter and other identity providers. Janrain Engage can reduce the necessity of managing many usernames and passwords for many websites.</p><p>To use Janrain Engage, choose a provider and sign in if prompted. Upon successful signin you will be returned to this site as a registered user. Next time you log in, you will be able to use the same 3rd party account instead of a regular username and password. You can have multiple 3rd party accounts if you like; just keep adding them here.</p>';
  $export['rpx_user_help_text'] = $strongarm;

  return $export;
}
