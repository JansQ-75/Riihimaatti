CREATE DATABASE  IF NOT EXISTS `riihimaattidb` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `riihimaattidb`;
-- MySQL dump 10.13  Distrib 8.0.40, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: riihimaattidb
-- ------------------------------------------------------
-- Server version	8.2.0

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
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

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
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `idtransaction` int NOT NULL AUTO_INCREMENT,
  `transaction_date` datetime NOT NULL,
  `withdrawal` decimal(10,2) NOT NULL,
  `idbank_account` int NOT NULL,
  `idcard` int DEFAULT NULL,
  PRIMARY KEY (`idtransaction`),
  KEY `fk_transaction2account_idx` (`idbank_account`),
  KEY `fk_transaction2card_idx` (`idcard`),
  CONSTRAINT `fk_transaction2account` FOREIGN KEY (`idbank_account`) REFERENCES `bank_account` (`idbank_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `fk_transaction2card` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

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
UPDATE bank_account SET balance=balance+amount WHERE idbank_account=accountId AND (balance+amount) <= credit_limit;
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
UPDATE bank_account SET balance=balance-amount WHERE idbank_account=accountId AND balance >= amount;
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
/*!50003 SET character_set_client  = utf8mb3 */ ;
/*!50003 SET character_set_results = utf8mb3 */ ;
/*!50003 SET collation_connection  = utf8mb3_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'NO_AUTO_VALUE_ON_ZERO' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `showTransactions`(IN accountId INT, IN offsetValue int)
BEGIN
START TRANSACTION;
SELECT * 
FROM transaction where idbank_account=accountId order by transaction_date desc limit 10 offset offsetValue;
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

-- Dump completed on 2025-01-26 21:52:18
