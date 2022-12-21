CREATE TABLE Position
(
  PositionId INTEGER NOT NULL UNIQUE,
  Longitude  REAL    NOT NULL,
  Latitude   REAL    NOT NULL,
  PRIMARY KEY (PositionId AUTOINCREMENT)
);

CREATE TABLE Track
(
  TrackId    INTEGER NOT NULL UNIQUE,
  Name       TEXT    NOT NULL,
  Finishline INTEGER NOT NULL,
  Startline  INTEGER NULL    ,
  PRIMARY KEY (TrackId AUTOINCREMENT),
  FOREIGN KEY (Finishline) REFERENCES Position (PositionId),
  FOREIGN KEY (Startline) REFERENCES Position (PositionId)
);

CREATE TABLE Session
(
  SessionId INTEGER NOT NULL UNIQUE,
  TrackId   INTEGER NOT NULL,
  -- Date of Session
  Date      TEXT    NOT NULL,
  -- time of session
  Time      TEXT    NOT NULL,
  PRIMARY KEY (SessionId AUTOINCREMENT),
  FOREIGN KEY (TrackId) REFERENCES Track (TrackId)
);

CREATE TABLE Lap
(
  LapId     INTEGER NOT NULL UNIQUE,
  SessionId INTEGER NOT NULL,
  LapIndex  INTEGER NOT NULL,
  PRIMARY KEY (LapId AUTOINCREMENT),
  FOREIGN KEY (SessionId) REFERENCES Session (SessionId)
);

CREATE TABLE Sektor
(
  PositionId  INTEGER NOT NULL UNIQUE,
  TrackId     INTEGER NOT NULL,
  SektorIndex INTEGER NOT NULL,
  PRIMARY KEY (PositionId, TrackId),
  FOREIGN KEY (PositionId) REFERENCES Position (PositionId),
  FOREIGN KEY (TrackId) REFERENCES Track (TrackId)
);

CREATE TABLE SektorTime
(
  SektorTimeId INTEGER NOT NULL UNIQUE,
  LapId        INTEGER NOT NULL,
  SektorIndex  INTEGER NOT NULL,
  Time         TEXT    NOT NULL,
  PRIMARY KEY (SektorTimeId AUTOINCREMENT),
  FOREIGN KEY (LapId) REFERENCES Lap (LapId)
);


