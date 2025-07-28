(register-command "test"
    (lambda (args client)
        (send-message client "hi from guile")))
