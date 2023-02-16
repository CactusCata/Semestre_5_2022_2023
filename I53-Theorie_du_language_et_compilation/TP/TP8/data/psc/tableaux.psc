DEBUT
    VAR n;
    n <- 8;
    VAR array[n];
    array[0] <- 6;
    array[1] <- 5;
    array[2] <- 3;
    array[3] <- 1;
    array[4] <- 8;
    array[5] <- 7;
    array[6] <- 2;
    array[7] <- 4;
    
    VAR j;


    VAR i;
    VAR tmp;
    i <- 0;

    TQ i < n FAIRE
        AFFICHER array[i];
        i <- i + 1;
    FTQ

FIN