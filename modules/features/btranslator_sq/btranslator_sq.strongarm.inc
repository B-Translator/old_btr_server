<?php
/**
 * @file
 * btranslator_sq.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function btranslator_sq_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_domain';
  $strongarm->value = 'l10n-sq';
  $export['disqus_domain'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_publickey';
  $strongarm->value = 'iK4bWgbfIrGm5JPRiG8igoNrf0zVW6PxiBEZ2JgwVEJrd4OjPCmr8Vt7p7cZwwEh';
  $export['disqus_publickey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_secretkey';
  $strongarm->value = '84QxPGVk4cx61FfFDquLO1x5Kfljdu6CK34qCP0pM83URlywP47e5xHXGKhN6EHa';
  $export['disqus_secretkey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'disqus_userapikey';
  $strongarm->value = 'jY36xKWOn1MibB0RiZ2zonErZfEx0q6h0SF9Ht5zwsAP0dSFpSBKNSufLfiTsI6y';
  $export['disqus_userapikey'] = $strongarm;

  return $export;
}
