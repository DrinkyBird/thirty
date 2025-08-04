(register-command "test"
    (lambda (args client)
        (send-message client (string-append "hi " (client-name client) " from guile") 'announcement)))
