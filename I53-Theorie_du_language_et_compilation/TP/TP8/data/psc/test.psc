DEBUT
    VAR n;
    n <- 4;
    VAR array[n];
    array[0] <- 2;
    array[1] <- 6;
    array[2] <- 4;
    array[3] <- 0;

    VAR i;
    i <- 0;

    TQ i < n FAIRE
        AFFICHER i;
        AFFICHER array[i];
        i <- i + 1;
    FTQ 
FIN