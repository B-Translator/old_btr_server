<?php
/**
 * @file
 * btranslator_layout.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function btranslator_layout_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => '1',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: main-menu:contact
  $menu_links['main-menu:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: main-menu:node/1
  $menu_links['main-menu:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => 'About this website.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: main-menu:node/9
  $menu_links['main-menu:node/9'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/9',
    'router_path' => 'node/%',
    'link_title' => 'Udhëzuesi i Përkthyesit',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: main-menu:translations
  $menu_links['main-menu:translations'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'translations',
    'router_path' => 'translations',
    'link_title' => 'Përkthimet',
    'options' => array(
      'attributes' => array(
        'title' => 'Votimi i përkthimeve dhe sugjerime përkthimesh.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: navig-menu:contact
  $menu_links['navig-menu:contact'] = array(
    'menu_name' => 'navig-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-46',
  );
  // Exported menu link: navig-menu:node/1
  $menu_links['navig-menu:node/1'] = array(
    'menu_name' => 'navig-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-47',
  );
  // Exported menu link: navig-menu:node/9
  $menu_links['navig-menu:node/9'] = array(
    'menu_name' => 'navig-menu',
    'link_path' => 'node/9',
    'router_path' => 'node/%',
    'link_title' => 'Udhëzuesi',
    'options' => array(
      'attributes' => array(
        'title' => 'Disa udhëzime lidhur me përkthimet.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: navig-menu:translations
  $menu_links['navig-menu:translations'] = array(
    'menu_name' => 'navig-menu',
    'link_path' => 'translations',
    'router_path' => 'translations',
    'link_title' => 'Përkthimet',
    'options' => array(
      'attributes' => array(
        'title' => 'Shiko një përkthim të rastësishëm.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: navig-menu:translations/search
  $menu_links['navig-menu:translations/search'] = array(
    'menu_name' => 'navig-menu',
    'link_path' => 'translations/search',
    'router_path' => 'translations/search',
    'link_title' => 'Fjalori',
    'options' => array(
      'query' => array(
        'project' => 'vocabulary',
        'lng' => 'sq',
      ),
      'attributes' => array(
        'title' => 'Shiko fjalët e fjalorit.',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('Contact');
  t('Fjalori');
  t('Home');
  t('Përkthimet');
  t('Udhëzuesi');
  t('Udhëzuesi i Përkthyesit');


  return $menu_links;
}
