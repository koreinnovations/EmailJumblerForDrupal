<?php

/**
 * Generate a random email address 
 * 
 * @return string Random email address
 */
function emailanonymizer_generate_address() {

  $random_part = emailanonymizer_random_string(20);
  $encoded_email = sprintf('%s@%s', $random_part, emailanonymizer_get_domain());

  return $encoded_email;
}

/**
 * Returns the domain to be used for anonymous emails
 */
function emailanonymizer_get_domain() {
  return variable_get('emailanonymizer_email_domain', $_SERVER['HTTP_HOST']);
}

/**
 * Generate and return a random string of characters.
 * @param int Length of the random string
 * @return A randomly-generated string
 */
function emailanonymizer_random_string($length = 20) {
  if (!ereg("^[0-9]+$", $length))
    return(-1);

  if ($length < 1 || $length > 65536)
    return(-1);

  srand((double) microtime() * 1000000);

  $string = '';

  while (strlen($string) != $length) {
    $type = rand(1, 3);
    if ($type == 1)
      $string = $string . chr(rand(48, 57));
    if ($type == 2)
      $string = $string . chr(rand(65, 90));
    if ($type == 3)
      $string = $string . chr(rand(97, 122));
  }

  return($string);
}

function emailanonymizer_get_anonymized_email($ref_id, $ref_type = 'comment') {
  $sql = "SELECT * FROM {emailanonymizer_email_mapping} WHERE ref_id = %d AND ref_type = '%s'";
  $result = db_query($sql, $ref_id, $ref_type);

  return db_fetch_object($result);
}