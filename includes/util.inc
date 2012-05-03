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
  return variable_get('', $_SERVER['HTTP_HOST']);
}

/**
 * Generate and return a random string of characters.
 * @param int Length of the random string
 * @return A randomly-generated string
 */
function emailanonymizer_random_string($max = 20) {
  $chars = explode(" ", "a b c d e f g h i j k l m n o p q r s t u v w x y z 0 1 2 3 4 5 6 7 8 9");
  for ($i = 0; $i < $max; $i++) {
    $rnd = array_rand($chars);
    $rtn .= base64_encode(md5($chars[$rnd]));
  }
  return substr(str_shuffle(strtolower($rtn)), 0, $max);
}