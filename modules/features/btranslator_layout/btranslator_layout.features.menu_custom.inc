<?php
/**
 * @file
 * btranslator_layout.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function btranslator_layout_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: navig-menu.
  $menus['navig-menu'] = array(
    'menu_name' => 'navig-menu',
    'title' => 'Navig Menu',
    'description' => 'A menu of most important link that is displayed on the left sidebar. The main reason for using it is that the main menu is not displayed correctly on smartphones.',
  );
  // Exported menu: user-menu.
  $menus['user-menu'] = array(
    'menu_name' => 'user-menu',
    'title' => 'User menu',
    'description' => 'The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('A menu of most important link that is displayed on the left sidebar. The main reason for using it is that the main menu is not displayed correctly on smartphones.');
  t('Main menu');
  t('Navig Menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');
  t('The <em>User</em> menu contains links related to the user\'s account, as well as the \'Log out\' link.');
  t('User menu');


  return $menus;
}
