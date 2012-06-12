**Email Jumbler for Drupal**

Enables Craigslist-style "anonymization" of email addresses on node comments. An 
anonymous user can post their comment, enter their name and email, and choose 
to expose a "fake" email address that will route to their real email address.


### Note

This module was designed to work with a Google apps account that has IMAP turned 
on.  It has not been tested with other email providers, although we do not 
forsee any problem adapting it for other providers.


### How it works

Generates random email addresses at a specified domain to mask the real email
addresses of people who post content or comments on your website.  These random
email addresses are not actual accounts on your mail server; rather they are all
sent to a "catch-all" address.  

This script downloads mail from the catch-all account (using IMAP) and looks up
the recipients against a database table that maps fake emails to real emails.
If matches are found, the messages are forwarded to the appropriate destinations.


### Instructions

1. Set up a Google apps account
1. Create an account to act as a "catch-all" domain.  This will catch emails 
sent to the randomly-generated addresses created by this module.
1. Turn on IMAP for this account
1. Install and enable this module.
1. From the module's configuration page, set the IMAP credentials, as well as the
domain name for your fake email addresses.  (example: If you want your fake 
addresses to end in @mydomain.com, you would put "mydomain.com" on the 
configuration page.
1. The routing will be done automatically any time Drupal cron runs.