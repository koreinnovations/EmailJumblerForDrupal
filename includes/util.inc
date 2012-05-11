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

function emailanonymizer_generate_original_from_encoded_email($encoded_email) {
  $sql = "SELECT * FROM {emailanonymizer_email_mapping} WHERE encoded_email = '%s'";
  $result = db_query($sql, $encoded_email);
  return db_fetch_object($result);
}

function emailanonymizer_do_email_routing() {
  /* credentials for catch-all account to gmail */
  $hostname = variable_get('emailanonymizer_imap_hostname', '');
  $username = variable_get('emailanonymizer_imap_username', '');
  $password = variable_get('emailanonymizer_imap_password', '');

  $count = 0;
  $results = array();

  /* try to connect */
  $inbox = imap_open($hostname, $username, $password) or die('Cannot connect to Gmail: ' . imap_last_error());
  $msgnos = imap_search($inbox, 'UNSEEN');
  if (!empty($msgnos)) {
    foreach ($msgnos as $msg) {
      $header = imap_headerinfo($inbox, $msg);
      $sender_name = $header->sender[0]->personal;
      $receiver = $header->to[0]->mailbox . '@' . $header->to[0]->host;
      $sender_email = $header->from[0]->mailbox . '@' . $header->from[0]->host;
      $subject = $header->subject;
      $body = imap_qprint(imap_fetchbody($inbox, $msg, 1));
      $original_email = emailanonymizer_generate_original_from_encoded_email($receiver);

      mail($original_email->original_email, $subject, $body, 'From: ' . $sender_email, '-f ' . $sender_email);

      $count++;
      $message = 'Sender Name:' . $sender_name . '</br>Sender Email:' . $sender_email . '</br>Receiver:' . $receiver . '</br>Subject:' . $subject . '</br>Original Email:' . $original_email->original_email . '</br></br>';
      $results[] = $message;
      watchdog('anonymizer', $message);
    }
  }
  else {
    $message = "No new messages. Try sending one and then revisit.";
    $results[] = $message;
    watchdog('anonymizer', $message);
  }

  return array(
      'count' => $count,
      'results' => $results,
  );
}
