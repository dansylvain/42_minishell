#!/usr/bin/expect


# Lance le programme `cat`
spawn rev

# Attend que `cat` soit prêt
expect "seblin@Laptop ~ $"

# Envoie la chaîne "0x004" à `cat`
send "crapeau"

# Simule l'envoi de Control-D pour indiquer la fin de l'entrée
send "\r\x04"

# Fin du script
expect eof

