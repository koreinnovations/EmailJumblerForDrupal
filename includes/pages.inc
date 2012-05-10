<?php

function emailanonymizer_page_email_routing() {
  $routing_result = emailanonymizer_do_email_routing();

  return implode("\n", $routing_result['results']);
}
