DEBUT
    VAR n;
	VAR a;
	VAR b;
	VAR c;
	VAR i;

	LIRE n;
	SI n = 0 ALORS
		AFFICHER 0;
	FSI

	SI n = 1 ALORS
		AFFICHER 1;
	SINON
		a <- 1;
		b <- 1;
		i <- 2;
		TQ i<n FAIRE
			c <- a+b;
			a <- b;
			b <- c;
			i <- i+1;
            AFFICHER c;
		FTQ
    FSI
FIN