<?php


function emailanonymizer_page_email_routing() {
  /* credentials for catch-all account to gmail */
  $hostname = variable_get('emailanonymizer_imap_hostname', '');
  $username = variable_get('emailanonymizer_imap_username', '');
  $password = variable_get('emailanonymizer_imap_password', '');

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

      $final .= 'Sender Name:' . $sender_name . '</br>Sender Email:' . $sender_email . '</br>Receiver:' . $receiver . '</br>Subject:' . $subject . '</br>Original Email:' . $original_email->original_email . '</br></br>';
    }
  }
  else {
    $final = "No new messages. Try sending one and then revisit.";
  }

  return $final;
}
