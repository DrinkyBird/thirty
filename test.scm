(register-command "test"
    (lambda (args client)
        (send-message client (string-append "hi " (client-name client) " from guile") 'announcement)))

(register-command "args"
    (lambda (args client)
        (display args)(newline)
        (let lp ((rem args))
            (when (pair? rem)
                (send-message client (car rem))
                (lp (cdr rem))))))

(register-command "block"
    (lambda (args client)
        (map-set-block! (server-map) 5 60 5 'cyan_wool)))

(handle-event 'client-move
    (lambda (client x y z)
        (map-set-block!
            (server-map)
            x
            (- y 2)
            z
            (+ (random 15) 21))))
