<?php
$content_dir = dirname(__FILE__) . '/content-sq';

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title    = 'Udhëzuesi i Përkthyesit';
$node->language = LANGUAGE_NONE;
$node->path = array('alias' => 'udhezuesi');
$node->menu = array(
  'enabled' => 1,
  'module' => 'menu',
  //'hidden' => 0,
  'link_title' => 'Udhëzuesi i Përkthyesit',
  'parent' => 'main-menu:0',
  'weight' => 5,
  'menu_name' => 'main-menu',
);
$node = node_submit($node);
node_save($node);

// get the book_id
$book_id = $node->nid;

$node->book['bid'] = $book_id;
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Si të Përkthejmë Programet në Ubuntu';
$node->path = array('alias' => 'si-te-perkthejme-programet-ne-ubuntu');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = file_get_contents("$content_dir/si-te-perkthejme-programet-ne-ubuntu.html");

$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Instalimi i Gjuhës Shqipe në Ubuntu';
$node->path = array('alias' => 'ubuntu-shqip');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = file_get_contents("$content_dir/ubuntu-shqip.html");
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Instalimi i Tastierës Shqipe në Ubuntu';
$node->path = array('alias' => 'tastiera-shqipe');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = file_get_contents("$content_dir/tastiera-shqipe.html");
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'book';
node_object_prepare($node);

$node->title = 'Instalimi i Fjalorit Drejtshkrimor';
$node->path = array('alias' => 'fjalori-drejtshkrimor');
$node->book['bid'] = $book_id;
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   = file_get_contents("$content_dir/fjalori-drejtshkrimor.html");
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'blog';
node_object_prepare($node);

$node->title = 'Visualization of Translating GNOME Into Albanian';
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['value']   =  file_get_contents("$content_dir/visualization-gnome-translation.html");
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'page';
node_object_prepare($node);

$node->title = 'About';
$node->path = array('alias' => 'about');
$node->menu = array(
  'enabled' => 1,
  'module' => 'menu',
  'link_title' => 'About',
  'parent' => 'main-menu:0',
  'weight' => 20,
  'menu_name' => 'main-menu',
);
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'full_html';
$node->body[LANGUAGE_NONE][0]['summary']   = file_get_contents("$content_dir/about.html");
$node->body[LANGUAGE_NONE][0]['value']   = file_get_contents("$content_dir/about.html");
$node = node_submit($node);
node_save($node);

/* ---------------------------- */

$node = new stdClass();
$node->type = 'blog';
node_object_prepare($node);

$node->title = 'Updating Drupal With Drush';
$node->language = LANGUAGE_NONE;
$node->body[LANGUAGE_NONE][0]['format']  = 'plain_text';
$node->body[LANGUAGE_NONE][0]['value']   = file_get_contents("$content_dir/updating-drupal.txt");
$node = node_submit($node);
node_save($node);

?>