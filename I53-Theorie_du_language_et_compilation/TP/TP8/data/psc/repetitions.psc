DEBUT
    VAR n; # 22 9
    VAR x; # 23 1
    VAR y; # 24 2
    VAR temp; # 25 1
    LIRE n;
    x <- 1;
    y <- 1;
    TQ n > 0 FAIRE
        temp <- x;
        y <- y+x;
        x <- temp;
        n <- n-1;
    FTQ
    AFFICHER y;
FIN