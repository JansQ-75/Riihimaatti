CREATE DATABASE  IF NOT EXISTS `riihimaattidb` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `riihimaattidb`;
-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: riihimaattidb
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `access_rights`
--

DROP TABLE IF EXISTS `access_rights`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `access_rights` (
  `idaccess_rights` int NOT NULL AUTO_INCREMENT,
  `idcard` int NOT NULL,
  `idbank_account` int NOT NULL,
  PRIMARY KEY (`idaccess_rights`),
  KEY `fk_access2card_idx` (`idcard`),
  KEY `fk_access2account_idx` (`idbank_account`),
  CONSTRAINT `fk_access2account` FOREIGN KEY (`idbank_account`) REFERENCES `bank_account` (`idbank_account`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_access2card` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `access_rights`
--

LOCK TABLES `access_rights` WRITE;
/*!40000 ALTER TABLE `access_rights` DISABLE KEYS */;
INSERT INTO `access_rights` VALUES (1,1,1),(2,2,2),(3,3,3),(4,3,4),(5,4,5),(6,5,6),(7,6,7);
/*!40000 ALTER TABLE `access_rights` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bank_account`
--

DROP TABLE IF EXISTS `bank_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bank_account` (
  `idbank_account` int NOT NULL AUTO_INCREMENT,
  `bank_account_number` varchar(20) NOT NULL,
  `account_type` varchar(15) NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `credit_limit` decimal(10,2) DEFAULT NULL,
  `idcustomer` int NOT NULL,
  PRIMARY KEY (`idbank_account`),
  UNIQUE KEY `idbank_account_number_UNIQUE` (`bank_account_number`),
  KEY `fk_account2customer_idx` (`idcustomer`),
  CONSTRAINT `fk_account2customer` FOREIGN KEY (`idcustomer`) REFERENCES `customer` (`idcustomer`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bank_account`
--

LOCK TABLES `bank_account` WRITE;
/*!40000 ALTER TABLE `bank_account` DISABLE KEYS */;
INSERT INTO `bank_account` VALUES (1,'FI11221122','debit',1677.12,0.00,1),(2,'FI44556644','credit',640.00,3000.00,2),(3,'FI66778899','debit',2080.00,0.00,3),(4,'FI55885588','credit',310.00,1000.00,3),(5,'FI45645645','credit',0.00,3000.00,4),(6,'FI44664466','debit',6500.00,0.00,5),(7,'FI9512648','credit',0.00,6000.00,2);
/*!40000 ALTER TABLE `bank_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL AUTO_INCREMENT,
  `cardnumber` int NOT NULL,
  `pin` varchar(255) NOT NULL,
  `idcustomer` int NOT NULL,
  `type` varchar(15) NOT NULL,
  `locked_status` tinyint NOT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `cardnumber_UNIQUE` (`cardnumber`),
  KEY `fk_card2customer_idx` (`idcustomer`),
  CONSTRAINT `fk_card2customer` FOREIGN KEY (`idcustomer`) REFERENCES `customer` (`idcustomer`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (0,0,'$2a$10$Ua1Dr2Cfau8bfv/Q1CdmTeSK/fLYy3m6wN/W5MYvu6rSioVfaVmjm',0,'debit',0),(1,664488,'$2a$10$LJcQBX7QLOmg03lSpoWQhu63N2ADU.s7ozZnj/qtnvIzU83FpyuDa',1,'debit',0),(2,254488,'$2a$10$76wov5DTNrlJNzLPm3sYGepidoOmFitNgiYdv7.bWgJevGxSlSKLi',2,'credit',0),(3,559188,'$2a$10$O8.er0h8bg4NY.S8XWrr5uMT/.5v1Zht7dbqrwrGxQLwyp6kEflIG',3,'debit/credit',0),(4,548988,'$2a$10$MbB3Ki6PvNx1rBqqo.PE7ukrQYMvNf5H5kNF3Uzs6Pb02MQgqcvXO',4,'credit',0),(5,656565,'$2a$10$0r0CWLvTK08HKlguCu2RtOpXnTBdqb2x4v/zs.fkYG9fwVjGWufam',5,'debit',0),(6,787878,'$2a$10$d5osoRsshO6JVibQxxehwe/E8ymXkZi.kCcsvTsXx.TAtpWG17UyG',6,'debit',0);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `idcustomer` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  `address` varchar(45) NOT NULL,
  `phone` varchar(15) NOT NULL,
  PRIMARY KEY (`idcustomer`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (0,'Super','Admin','Tiedonvaltatie 1','020202'),(1,'Liisa','Lamminen','Kotikatu 5','0405678673'),(2,'Tiina','Tamminen','Hetkosenkatu 5','040055673'),(3,'Teuvo','Tepponen','Tavistie 15','0507845123'),(4,'Leo','Keihäs','Koivukatu 2','0401245673'),(5,'Hemmo','Kuussalo','Tähtitie 6 B1','0407788673'),(6,'Henna','Himanen','Vilkaskatu 45','05012478673'),(7,'Pekka','Eversti','Uppotukintie 6','0401245787');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `idtransaction` int NOT NULL AUTO_INCREMENT,
  `transaction_date` timestamp NULL DEFAULT NULL,
  `withdrawal` decimal(10,2) NOT NULL,
  `idbank_account` int NOT NULL,
  `idcard` int DEFAULT NULL,
  PRIMARY KEY (`idtransaction`),
  KEY `fk_transaction2account_idx` (`idbank_account`),
  KEY `fk_transaction2card_idx` (`idcard`),
  CONSTRAINT `fk_transaction2account` FOREIGN KEY (`idbank_account`) REFERENCES `bank_account` (`idbank_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `fk_transaction2card` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=50 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,'2025-01-15 18:34:18',20.00,1,NULL),(2,'2025-01-21 08:30:13',20.00,1,1),(3,'2025-01-21 08:31:12',30.00,3,3),(4,'2025-01-21 08:32:12',50.00,3,NULL),(5,'2025-01-21 08:33:09',50.00,3,NULL),(6,'2025-01-21 08:38:12',60.00,3,3),(7,'2025-01-21 09:15:48',40.00,1,1),(8,'2025-01-21 09:24:40',150.00,2,2),(9,'2025-01-21 09:26:57',600.00,1,1),(10,'2025-01-21 09:26:57',150.00,2,2),(11,'2025-01-21 09:27:49',300.00,2,2),(12,'2025-01-28 11:27:12',30.00,2,2),(13,'2025-01-28 11:30:31',30.00,1,1),(14,'2025-01-28 22:13:14',10.00,1,1),(15,'2025-01-28 22:15:35',50.00,1,1),(16,'2025-01-28 22:21:55',30.00,3,3),(17,'2025-01-28 22:25:34',10.00,2,2),(18,'2025-01-29 17:49:01',20.00,1,1),(19,'2025-01-29 18:27:01',10.00,3,3),(20,'2025-01-29 18:37:04',10.00,4,3),(21,'2025-01-30 15:23:32',30.00,4,3),(22,'2025-01-30 21:45:41',40.00,1,1),(23,'2025-01-30 21:46:38',30.00,4,3),(24,'2025-01-30 21:46:38',50.00,1,1),(25,'2025-01-30 21:46:50',50.00,1,1),(26,'2025-01-30 21:47:00',100.00,1,1),(27,'2025-01-30 21:47:08',10.00,1,1),(28,'2025-01-30 21:47:18',60.00,1,1),(29,'2025-01-30 21:50:20',30.00,4,3),(30,'2025-01-30 21:50:20',60.00,1,1),(31,'2025-01-30 21:50:55',30.00,4,3),(32,'2025-01-30 21:50:55',60.00,1,1),(33,'2025-01-30 21:51:05',30.00,4,3),(34,'2025-01-30 21:51:05',60.00,1,1),(35,'2025-01-30 21:59:48',30.00,4,3),(36,'2025-01-30 21:59:48',60.00,1,1),(37,'2025-01-30 22:02:34',30.00,4,3),(38,'2025-01-30 22:02:34',60.00,1,1),(39,'2025-01-30 22:03:33',30.00,4,3),(40,'2025-01-30 22:03:33',60.00,1,1),(41,'2025-02-03 10:30:45',40.00,1,1),(42,'2025-02-03 10:35:57',50.00,1,1),(43,'2025-02-03 10:46:46',30.00,4,3),(44,'2025-02-03 10:46:46',60.00,1,1),(45,'2025-02-03 10:46:46',50.00,1,1),(46,'2025-02-03 10:50:07',30.00,4,3),(47,'2025-02-03 10:50:07',60.00,1,1),(48,'2025-02-03 10:50:07',50.00,1,1),(49,'2025-02-03 11:03:14',20.00,1,1);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'riihimaattidb'
--
/*!50003 DROP PROCEDURE IF EXISTS `atm_transactions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `atm_transactions`(IN account INT)
BEGIN
SELECT transaction.transaction_date, transaction.withdrawal, bank_account.bank_account_number, card.cardnumber 
FROM transaction 
JOIN bank_account ON transaction.idbank_account=bank_account.idbank_account 
LEFT JOIN card ON transaction.idcard=card.idcard 
WHERE bank_account.idbank_account=account;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `makeCreditWithdrawal` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `makeCreditWithdrawal`(IN accountId INT, IN cardId INT, IN amount DOUBLE)
BEGIN
DECLARE test1 INT DEFAULT 0;
START TRANSACTION;
UPDATE bank_account SET balance=balance+amount WHERE idbank_account=accountId AND (balance+amount) <= credit_limit AND account_type='credit';
SET test1=ROW_COUNT();
	IF (test1=1) THEN
		COMMIT;
		INSERT INTO transaction (transaction_date, withdrawal, idbank_account, idcard)
		VALUES (NOW(), amount, accountId, cardId);
	ELSE
		ROLLBACK;
	END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `makeDebitWithdrawal` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `makeDebitWithdrawal`(IN accountId INT, IN cardId INT, IN amount DOUBLE)
BEGIN
DECLARE test1 INT DEFAULT 0;
START TRANSACTION;
UPDATE bank_account SET balance=balance-amount WHERE idbank_account=accountId AND balance >= amount AND account_type='debit';
SET test1=ROW_COUNT();
	IF (test1=1) THEN
		COMMIT;
		INSERT INTO transaction (transaction_date, withdrawal, idbank_account, idcard)
		VALUES (NOW(), amount, accountId, cardId);
	ELSE
		ROLLBACK;
	END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `showTransactions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `showTransactions`(IN accountId INT, IN offsetValue int)
BEGIN
START TRANSACTION;
SELECT date_format(t.transaction_date, '%d.%m.%Y %H:%i:%s') AS transaction_date, t.withdrawal, b.bank_account_number, c.cardnumber 
FROM transaction t 
join bank_account b on t.idbank_account=b.idbank_account 
join access_rights a on b.idbank_account=a.idbank_account 
join card c on a.idcard=c.idcard 
where b.idbank_account=accountId 
order by t.transaction_date desc limit 10 offset offsetValue;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-02-04 14:32:34
