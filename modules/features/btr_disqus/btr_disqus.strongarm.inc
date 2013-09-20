<?php
/**
 * @file
 * btr_disqus.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btr_disqus_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_developer';
  $strongarm->value = 1;
  $export['disqus_developer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_domain';
  $strongarm->value = 'btranslator';
  $export['disqus_domain'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_inherit_login';
  $strongarm->value = 1;
  $export['disqus_inherit_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_localization';
  $strongarm->value = 1;
  $export['disqus_localization'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_location';
  $strongarm->value = 'block';
  $export['disqus_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_nodetypes';
  $strongarm->value = array(
    'blog' => 'blog',
    'article' => 'article',
    'book' => 'book',
    'mass_contact' => 'mass_contact',
    'page' => 'page',
    'projects' => 'projects',
    'simplenews' => 'simplenews',
  );
  $export['disqus_nodetypes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_publickey';
  $strongarm->value = 'HrPP8K7egZywd6EjoDIb7TwINf7bpfBRGuKe0JgmwfIm06RyQdH6cL3VbKH6LGf6';
  $export['disqus_publickey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_secretkey';
  $strongarm->value = 'OxaVaADZmMJSZ7rlM8cW85qr7i7V5rLNRJEDgiszk9zD0HlK1MXAProqteah2ahM';
  $export['disqus_secretkey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_sso';
  $strongarm->value = 1;
  $export['disqus_sso'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_userapikey';
  $strongarm->value = '';
  $export['disqus_userapikey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_weight';
  $strongarm->value = '100';
  $export['disqus_weight'] = $strongarm;

  return $export;
}
