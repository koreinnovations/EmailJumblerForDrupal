<?php

function emailanonymizer_admin_settings_form() {
  $form = array();

  $form['emailanonymizer_email_domain'] = array(
      '#title' => t('Email Domain Name'),
      '#type' => 'textfield',
      '#default_value' => emailanonymizer_get_domain(),
      '#description' => t('This will be the part of the anonymous email address after the @'),
  );

  
  $form['emailanonymizer_imap_hostname'] = array(
      '#title' => t('IMAP Hostname'),
      '#type' => 'textfield',
      '#default_value' => variable_get('emailanonymizer_imap_hostname', ''),
  );

  
  $form['emailanonymizer_imap_username'] = array(
      '#title' => t('IMAP Username'),
      '#type' => 'textfield',
      '#default_value' => variable_get('emailanonymizer_imap_username', ''),
  );

  $form['emailanonymizer_imap_password'] = array(
      '#title' => t('IMAP Password'),
      '#type' => 'password',
      '#default_value' => variable_get('emailanonymizer_imap_password', ''),
  );

  return system_settings_form($form);
}