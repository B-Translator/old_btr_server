<?php
/**
 * @file
 * btr_disqus.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function btr_disqus_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer disqus.
  $permissions['administer disqus'] = array(
    'name' => 'administer disqus',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'disqus',
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

  return $permissions;
}
