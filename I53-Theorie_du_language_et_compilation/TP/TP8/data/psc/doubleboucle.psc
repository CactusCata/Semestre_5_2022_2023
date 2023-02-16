DEBUT
    VAR n;
	VAR j;
	VAR i;

    n <- 10;
    i <- 0;

	TQ i < n FAIRE
        j <- 0;
        TQ j < n FAIRE
            AFFICHER i * j;
            j <- j + 1;
        FTQ
        i <- i + 1;
	FTQ
FIN