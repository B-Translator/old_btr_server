<?php
/**
 * @file
 * btranslator_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btranslator_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access all views.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: access comments.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: access dashboard.
  $permissions['access dashboard'] = array(
    'name' => 'access dashboard',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'dashboard',
  );

  // Exported permission: access devel information.
  $permissions['access devel information'] = array(
    'name' => 'access devel information',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'devel',
  );

  // Exported permission: access drupalchat.
  $permissions['access drupalchat'] = array(
    'name' => 'access drupalchat',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'drupalchat',
  );

  // Exported permission: access drupalchat all logs.
  $permissions['access drupalchat all logs'] = array(
    'name' => 'access drupalchat all logs',
    'roles' => array(),
    'module' => 'drupalchat',
  );

  // Exported permission: access drupalchat own logs.
  $permissions['access drupalchat own logs'] = array(
    'name' => 'access drupalchat own logs',
    'roles' => array(),
    'module' => 'drupalchat',
  );

  // Exported permission: access news feeds.
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'aggregator',
  );

  // Exported permission: access printer-friendly version.
  $permissions['access printer-friendly version'] = array(
    'name' => 'access printer-friendly version',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: access rules debug.
  $permissions['access rules debug'] = array(
    'name' => 'access rules debug',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: access site in maintenance mode.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: access site reports.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'system',
  );

  // Exported permission: access site-wide contact form.
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'contact',
  );

  // Exported permission: access toolbar.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'toolbar',
  );

  // Exported permission: access user contact forms.
  $permissions['access user contact forms'] = array(
    'name' => 'access user contact forms',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'contact',
  );

  // Exported permission: access user profiles.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
      2 => 'moderator',
      3 => 'translator',
    ),
    'module' => 'user',
  );

  // Exported permission: add content to books.
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: administer CAPTCHA settings.
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'captcha',
  );

  // Exported permission: administer actions.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer blocks.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'block',
  );

  // Exported permission: administer book outlines.
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'book',
  );

  // Exported permission: administer comments.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: administer configuration management.
  $permissions['administer configuration management'] = array(
    'name' => 'administer configuration management',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'configuration_ui',
  );

  // Exported permission: administer contact forms.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: administer content types.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: administer contexts.
  $permissions['administer contexts'] = array(
    'name' => 'administer contexts',
    'roles' => array(),
    'module' => 'context_ui',
  );

  // Exported permission: administer disqus.
  $permissions['administer disqus'] = array(
    'name' => 'administer disqus',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'disqus',
  );

  // Exported permission: administer drupalchat.
  $permissions['administer drupalchat'] = array(
    'name' => 'administer drupalchat',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'drupalchat',
  );

  // Exported permission: administer fb apps.
  $permissions['administer fb apps'] = array(
    'name' => 'administer fb apps',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'fb',
  );

  // Exported permission: administer features.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: administer filters.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: administer google analytics.
  $permissions['administer google analytics'] = array(
    'name' => 'administer google analytics',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: administer homebox.
  $permissions['administer homebox'] = array(
    'name' => 'administer homebox',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'homebox',
  );

  // Exported permission: administer honeypot.
  $permissions['administer honeypot'] = array(
    'name' => 'administer honeypot',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'honeypot',
  );

  // Exported permission: administer image styles.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'image',
  );

  // Exported permission: administer invitations.
  $permissions['administer invitations'] = array(
    'name' => 'administer invitations',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'invite',
  );

  // Exported permission: administer janrain engage.
  $permissions['administer janrain engage'] = array(
    'name' => 'administer janrain engage',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'rpx_ui',
  );

  // Exported permission: administer languages.
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'locale',
  );

  // Exported permission: administer mailsystem.
  $permissions['administer mailsystem'] = array(
    'name' => 'administer mailsystem',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mailsystem',
  );

  // Exported permission: administer menu.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: administer module filter.
  $permissions['administer module filter'] = array(
    'name' => 'administer module filter',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'module_filter',
  );

  // Exported permission: administer modules.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer news feeds.
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'aggregator',
  );

  // Exported permission: administer newsletters.
  $permissions['administer newsletters'] = array(
    'name' => 'administer newsletters',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: administer nodes.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: administer permissions.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: administer phpmailer settings.
  $permissions['administer phpmailer settings'] = array(
    'name' => 'administer phpmailer settings',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'phpmailer',
  );

  // Exported permission: administer profiler builder.
  $permissions['administer profiler builder'] = array(
    'name' => 'administer profiler builder',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'profiler_builder',
  );

  // Exported permission: administer recaptcha.
  $permissions['administer recaptcha'] = array(
    'name' => 'administer recaptcha',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'recaptcha',
  );

  // Exported permission: administer reroute email.
  $permissions['administer reroute email'] = array(
    'name' => 'administer reroute email',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'reroute_email',
  );

  // Exported permission: administer rules.
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: administer search.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: administer sharethis.
  $permissions['administer sharethis'] = array(
    'name' => 'administer sharethis',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'sharethis',
  );

  // Exported permission: administer simplenews settings.
  $permissions['administer simplenews settings'] = array(
    'name' => 'administer simplenews settings',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: administer simplenews subscriptions.
  $permissions['administer simplenews subscriptions'] = array(
    'name' => 'administer simplenews subscriptions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: administer site configuration.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer software updates.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer taxonomy.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: administer themes.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: administer unit tests.
  $permissions['administer unit tests'] = array(
    'name' => 'administer unit tests',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'simpletest',
  );

  // Exported permission: administer url aliases.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: administer users.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: administer uuid.
  $permissions['administer uuid'] = array(
    'name' => 'administer uuid',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'uuid',
  );

  // Exported permission: administer views.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: block IP addresses.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
    ),
    'module' => 'system',
  );

  // Exported permission: boost flush pages.
  $permissions['boost flush pages'] = array(
    'name' => 'boost flush pages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'boost',
  );

  // Exported permission: btranslator-admin.
  $permissions['btranslator-admin'] = array(
    'name' => 'btranslator-admin',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-export.
  $permissions['btranslator-export'] = array(
    'name' => 'btranslator-export',
    'roles' => array(
      0 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-flag.
  $permissions['btranslator-flag'] = array(
    'name' => 'btranslator-flag',
    'roles' => array(
      0 => 'contributor',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-import.
  $permissions['btranslator-import'] = array(
    'name' => 'btranslator-import',
    'roles' => array(
      0 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-resolve.
  $permissions['btranslator-resolve'] = array(
    'name' => 'btranslator-resolve',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-stats.
  $permissions['btranslator-stats'] = array(
    'name' => 'btranslator-stats',
    'roles' => array(
      0 => 'moderator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-suggest.
  $permissions['btranslator-suggest'] = array(
    'name' => 'btranslator-suggest',
    'roles' => array(
      0 => 'contributor',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: btranslator-vote.
  $permissions['btranslator-vote'] = array(
    'name' => 'btranslator-vote',
    'roles' => array(
      0 => 'contributor',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'l10n_feedback',
  );

  // Exported permission: bypass honeypot protection.
  $permissions['bypass honeypot protection'] = array(
    'name' => 'bypass honeypot protection',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'honeypot',
  );

  // Exported permission: bypass node access.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: bypass rules access.
  $permissions['bypass rules access'] = array(
    'name' => 'bypass rules access',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: cancel account.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: change own username.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: create article content.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: create blog content.
  $permissions['create blog content'] = array(
    'name' => 'create blog content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: create book content.
  $permissions['create book content'] = array(
    'name' => 'create book content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: create mass_contact content.
  $permissions['create mass_contact content'] = array(
    'name' => 'create mass_contact content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: create new books.
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'book',
  );

  // Exported permission: create page content.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: create projects content.
  $permissions['create projects content'] = array(
    'name' => 'create projects content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: create simplenews content.
  $permissions['create simplenews content'] = array(
    'name' => 'create simplenews content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: create url aliases.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: delete any article content.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any blog content.
  $permissions['delete any blog content'] = array(
    'name' => 'delete any blog content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any book content.
  $permissions['delete any book content'] = array(
    'name' => 'delete any book content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any mass_contact content.
  $permissions['delete any mass_contact content'] = array(
    'name' => 'delete any mass_contact content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any page content.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any projects content.
  $permissions['delete any projects content'] = array(
    'name' => 'delete any projects content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any simplenews content.
  $permissions['delete any simplenews content'] = array(
    'name' => 'delete any simplenews content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own article content.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own blog content.
  $permissions['delete own blog content'] = array(
    'name' => 'delete own blog content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own book content.
  $permissions['delete own book content'] = array(
    'name' => 'delete own book content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own fb_user authmap.
  $permissions['delete own fb_user authmap'] = array(
    'name' => 'delete own fb_user authmap',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'fb_user',
  );

  // Exported permission: delete own mass_contact content.
  $permissions['delete own mass_contact content'] = array(
    'name' => 'delete own mass_contact content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own page content.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own projects content.
  $permissions['delete own projects content'] = array(
    'name' => 'delete own projects content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own simplenews content.
  $permissions['delete own simplenews content'] = array(
    'name' => 'delete own simplenews content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 1.
  $permissions['delete terms in 1'] = array(
    'name' => 'delete terms in 1',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 2.
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: display disqus comments on profile.
  $permissions['display disqus comments on profile'] = array(
    'name' => 'display disqus comments on profile',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'disqus',
  );

  // Exported permission: edit any article content.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any blog content.
  $permissions['edit any blog content'] = array(
    'name' => 'edit any blog content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any book content.
  $permissions['edit any book content'] = array(
    'name' => 'edit any book content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any mass_contact content.
  $permissions['edit any mass_contact content'] = array(
    'name' => 'edit any mass_contact content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any page content.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any projects content.
  $permissions['edit any projects content'] = array(
    'name' => 'edit any projects content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any simplenews content.
  $permissions['edit any simplenews content'] = array(
    'name' => 'edit any simplenews content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit mimemail user settings.
  $permissions['edit mimemail user settings'] = array(
    'name' => 'edit mimemail user settings',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'mimemail',
  );

  // Exported permission: edit own article content.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own blog content.
  $permissions['edit own blog content'] = array(
    'name' => 'edit own blog content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own book content.
  $permissions['edit own book content'] = array(
    'name' => 'edit own book content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own comments.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: edit own extended permissions.
  $permissions['edit own extended permissions'] = array(
    'name' => 'edit own extended permissions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'fb_permission',
  );

  // Exported permission: edit own mass_contact content.
  $permissions['edit own mass_contact content'] = array(
    'name' => 'edit own mass_contact content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own page content.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own projects content.
  $permissions['edit own projects content'] = array(
    'name' => 'edit own projects content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own simplenews content.
  $permissions['edit own simplenews content'] = array(
    'name' => 'edit own simplenews content',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit terms in 1.
  $permissions['edit terms in 1'] = array(
    'name' => 'edit terms in 1',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 2.
  $permissions['edit terms in 2'] = array(
    'name' => 'edit terms in 2',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: execute php code.
  $permissions['execute php code'] = array(
    'name' => 'execute php code',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'devel',
  );

  // Exported permission: export nodes.
  $permissions['export nodes'] = array(
    'name' => 'export nodes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node_export',
  );

  // Exported permission: export own nodes.
  $permissions['export own nodes'] = array(
    'name' => 'export own nodes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node_export',
  );

  // Exported permission: manage features.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: manage own identities.
  $permissions['manage own identities'] = array(
    'name' => 'manage own identities',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'rpx_ui',
  );

  // Exported permission: mass contact administer.
  $permissions['mass contact administer'] = array(
    'name' => 'mass contact administer',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact archive messages.
  $permissions['mass contact archive messages'] = array(
    'name' => 'mass contact archive messages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact change default sender information.
  $permissions['mass contact change default sender information'] = array(
    'name' => 'mass contact change default sender information',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact include attachments.
  $permissions['mass contact include attachments'] = array(
    'name' => 'mass contact include attachments',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact override archiving.
  $permissions['mass contact override archiving'] = array(
    'name' => 'mass contact override archiving',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact override bcc.
  $permissions['mass contact override bcc'] = array(
    'name' => 'mass contact override bcc',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact override text format.
  $permissions['mass contact override text format'] = array(
    'name' => 'mass contact override text format',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact send messages.
  $permissions['mass contact send messages'] = array(
    'name' => 'mass contact send messages',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact send to users in the All Users category.
  $permissions['mass contact send to users in the All Users category'] = array(
    'name' => 'mass contact send to users in the All Users category',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'mass_contact',
  );

  // Exported permission: mass contact send to users in the Translators category.
  $permissions['mass contact send to users in the Translators category'] = array(
    'name' => 'mass contact send to users in the Translators category',
    'roles' => array(),
    'module' => 'mass_contact',
  );

  // Exported permission: opt-in or out of tracking.
  $permissions['opt-in or out of tracking'] = array(
    'name' => 'opt-in or out of tracking',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: override facebook stream details.
  $permissions['override facebook stream details'] = array(
    'name' => 'override facebook stream details',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'fb_stream',
  );

  // Exported permission: post comments.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: post to site-wide facebook stream.
  $permissions['post to site-wide facebook stream'] = array(
    'name' => 'post to site-wide facebook stream',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'fb_stream',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: search content.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: select account cancellation method.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: send invitations.
  $permissions['send invitations'] = array(
    'name' => 'send invitations',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'invite',
  );

  // Exported permission: send mass invitations.
  $permissions['send mass invitations'] = array(
    'name' => 'send mass invitations',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'invite',
  );

  // Exported permission: send newsletter.
  $permissions['send newsletter'] = array(
    'name' => 'send newsletter',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: skip CAPTCHA.
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'captcha',
  );

  // Exported permission: skip comment approval.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: submit translations to localization server.
  $permissions['submit translations to localization server'] = array(
    'name' => 'submit translations to localization server',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'l10n_client',
  );

  // Exported permission: subscribe to newsletters.
  $permissions['subscribe to newsletters'] = array(
    'name' => 'subscribe to newsletters',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: switch users.
  $permissions['switch users'] = array(
    'name' => 'switch users',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'devel',
  );

  // Exported permission: toggle disqus comments.
  $permissions['toggle disqus comments'] = array(
    'name' => 'toggle disqus comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'disqus',
  );

  // Exported permission: track invitations.
  $permissions['track invitations'] = array(
    'name' => 'track invitations',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'invite',
  );

  // Exported permission: translate interface.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'locale',
  );

  // Exported permission: use PHP for tracking visibility.
  $permissions['use PHP for tracking visibility'] = array(
    'name' => 'use PHP for tracking visibility',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: use PHP to import nodes.
  $permissions['use PHP to import nodes'] = array(
    'name' => 'use PHP to import nodes',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node_export',
  );

  // Exported permission: use advanced search.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: use on-page translation.
  $permissions['use on-page translation'] = array(
    'name' => 'use on-page translation',
    'roles' => array(
      0 => 'administrator',
      1 => 'translator',
    ),
    'module' => 'l10n_client',
  );

  // Exported permission: use text format filtered_html.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: use text format full_html.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'filter',
  );

  // Exported permission: view disqus comments.
  $permissions['view disqus comments'] = array(
    'name' => 'view disqus comments',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
      2 => 'authenticated user',
    ),
    'module' => 'disqus',
  );

  // Exported permission: view invite statistics.
  $permissions['view invite statistics'] = array(
    'name' => 'view invite statistics',
    'roles' => array(
      0 => 'administrator',
      1 => 'moderator',
      2 => 'translator',
    ),
    'module' => 'invite_stats',
  );

  // Exported permission: view own invite statistics.
  $permissions['view own invite statistics'] = array(
    'name' => 'view own invite statistics',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'invite_stats',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: withdraw own accepted invitations.
  $permissions['withdraw own accepted invitations'] = array(
    'name' => 'withdraw own accepted invitations',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'invite',
  );

  // Exported permission: withdraw own invitations.
  $permissions['withdraw own invitations'] = array(
    'name' => 'withdraw own invitations',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'invite',
  );

  return $permissions;
}
