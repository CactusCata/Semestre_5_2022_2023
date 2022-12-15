DROP SCHEMA IF EXISTS TP CASCADE;
CREATE SCHEMA TP;
SET search_path TO TP;

/*
procedure_Reservation(v_id_client INT, v_id_spectacle INT, nb_places INT)
-- Variables
v_client Client%ROWTYPE;
v_spectable Spectacle%ROWTYPE
*/

CREATE TABLE Spectacle (
  nomS VARCHAR(15) NOT NULL PRIMARY KEY,
  Nbplaces INTEGER NOT NULL,
  NbplacesLibres INTEGER NOT NULL,
  tarif DECIMAL(10, 2) NOT NULL
);

CREATE TABLE Client (
  nomC VARCHAR(10) NOT NULL PRIMARY KEY,
  Solde INTEGER NOT NULL
);

CREATE TABLE Reservation (
  nomC VARCHAR(10) NOT NULL REFERENCES Client,
  nomS VARCHAR(15) NOT NULL REFERENCES Spectacle,
  NbplacesReservees INT NOT NULL
);

INSERT INTO Client VALUES
('Quentin', 50),
('Grégoire', 50);

INSERT INTO Spectacle VALUES
('Harry Potter', 250, 250, 20);




-- On est obligé de mettre la commande de SET SESSION
-- dans à l'intérieur d'une transaction
BEGIN TRANSACTION;
SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ;
COMMIT;

CREATE OR REPLACE FUNCTION buyPlaceEvent()
RETURNS TRIGGER
AS $$
DECLARE spec Spectacle%ROWTYPE;
/*
DECLARE nbplacelibreA INTEGER;
DECLARE nbplaceLibreB INTEGER;
*/
  BEGIN

  SELECT * INTO spec
  FROM Spectacle
  WHERE Spectacle.nomS = new.nomS;

  IF (spec.NbplacesLibres - new.NbplacesReservees >= 0)
  THEN

    UPDATE Spectacle
    SET NbplacesLibres = NbplacesLibres - new.NbplacesReservees;

    RETURN new;
  ELSE
    RETURN NULL; -- annule la transaction
  END IF;

  /*SELECT SUM(NbplacesReservees) INTO nbplacelibreA
  FROM Reservation, Spectacle
  WHERE Reservation.nomS = new.nomS
  AND Reservation.nomS = Spectacle.nomS;

  SELECT Spectacle.Nbplaces - Spectacle.NbplacesLibres INTO nbplaceLibreB
  FROM Spectacle
  WHERE Spectacle.nomS = new.nomS;

  IF (nbplacelibreA = nbplaceLibreB)
  THEN
    COMMIT;
  ELSE
    ROLLBACK;
  END IF;
  */
  END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION changePlaceAmountEvent()
RETURNS TRIGGER
AS $$
DECLARE spec Spectacle%ROWTYPE;
DECLARE amount INT;

  BEGIN

  amount := new.NbplacesReservees - old.NbplacesReservees;

  SELECT * INTO spec
  FROM Spectacle
  WHERE Spectacle.nomS = new.nomS;

  IF (spec.NbplacesLibres - amount >= 0)
  THEN

    UPDATE Spectacle
    SET NbplacesLibres = NbplacesLibres - amount;

    RETURN new;
  ELSE
    RETURN NULL; -- annule la transaction
  END IF;

  END;
$$
LANGUAGE plpgsql;


CREATE TRIGGER buyPlaceEvent
BEFORE INSERT
ON Reservation
FOR EACH ROW
EXECUTE PROCEDURE buyPlaceEvent();

CREATE TRIGGER changePlaceAmountEvent
BEFORE UPDATE
ON Reservation
FOR EACH ROW
EXECUTE PROCEDURE changePlaceAmountEvent();


INSERT INTO Reservation VALUES
('Quentin', 'Harry Potter', 100);

SELECT *
FROM Reservation;

SELECT *
FROM Spectacle;

UPDATE Reservation
SET NbplacesReservees = 600
WHERE Reservation.nomC = 'Quentin'
AND Reservation.nomS = 'Harry Potter';

SELECT *
FROM Reservation;

SELECT *
FROM Spectacle;

BEGIN TRANSACTION;
SET SESSION TRANSACTION ISOLATION LEVEL SERIALIZABLE;
END;
