-- MySQL dump 10.13  Distrib 8.0.40, for Win64 (x86_64)
--
-- Host: 192.168.1.107    Database: riihimaattidb
-- ------------------------------------------------------
-- Server version	8.3.0

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
-- Dumping data for table `access_rights`
--

LOCK TABLES `access_rights` WRITE;
/*!40000 ALTER TABLE `access_rights` DISABLE KEYS */;
INSERT INTO `access_rights` VALUES (1,1,1),(2,2,2),(3,3,3),(4,3,4),(5,4,5),(6,5,6),(7,6,7);
/*!40000 ALTER TABLE `access_rights` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `bank_account`
--

LOCK TABLES `bank_account` WRITE;
/*!40000 ALTER TABLE `bank_account` DISABLE KEYS */;
INSERT INTO `bank_account` VALUES (1,'FI11221122','debit',560.00,0.00,1),(2,'FI44556644','credit',600.00,4000.00,2),(3,'FI66778899','debit',2120.00,0.00,3),(4,'FI55885588','credit',0.00,1000.00,3),(5,'FI45645645','credit',0.00,3000.00,4),(6,'FI44664466','debit',6500.00,0.00,5),(7,'FI9512648','credit',0.00,6000.00,2);
/*!40000 ALTER TABLE `bank_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (0,0,'$2a$10$Ua1Dr2Cfau8bfv/Q1CdmTeSK/fLYy3m6wN/W5MYvu6rSioVfaVmjm',0,'debit',0),(1,664488,'$2a$10$LJcQBX7QLOmg03lSpoWQhu63N2ADU.s7ozZnj/qtnvIzU83FpyuDa',1,'debit',0),(2,254488,'$2a$10$76wov5DTNrlJNzLPm3sYGepidoOmFitNgiYdv7.bWgJevGxSlSKLi',2,'credit',0),(3,559188,'$2a$10$O8.er0h8bg4NY.S8XWrr5uMT/.5v1Zht7dbqrwrGxQLwyp6kEflIG',3,'debit/credit',0),(4,548988,'$2a$10$MbB3Ki6PvNx1rBqqo.PE7ukrQYMvNf5H5kNF3Uzs6Pb02MQgqcvXO',4,'credit',0),(5,656565,'$2a$10$0r0CWLvTK08HKlguCu2RtOpXnTBdqb2x4v/zs.fkYG9fwVjGWufam',5,'debit',0),(6,787878,'$2a$10$d5osoRsshO6JVibQxxehwe/E8ymXkZi.kCcsvTsXx.TAtpWG17UyG',6,'debit',0);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (0,'Super','Admin','Tiedonvaltatie 1','020202'),(1,'Liisa','Lamminen','Kotikatu 5','0405678673'),(2,'Tiina','Tamminen','Hetkosenkatu 5','040055673'),(3,'Teuvo','Tepponen','Tavistie 15','0507845123'),(4,'Leo','Keihäs','Koivukatu 2','0401245673'),(5,'Hemmo','Kuussalo','Tähtitie 6 B1','0407788673'),(6,'Henna','Himanen','Vilkaskatu 45','05012478673'),(7,'Pekka','Eversti','Uppotukintie 6','0401245787');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,'2025-01-15 20:34:18',20.00,1,NULL),(2,'2025-01-21 10:30:13',20.00,1,1),(3,'2025-01-21 10:31:12',30.00,3,3),(4,'2025-01-21 10:32:12',50.00,3,NULL),(5,'2025-01-21 10:33:09',50.00,3,NULL),(6,'2025-01-21 10:38:12',60.00,3,3),(7,'2025-01-21 11:15:48',40.00,1,1),(8,'2025-01-21 11:24:40',150.00,2,2),(9,'2025-01-21 11:26:57',600.00,1,1),(10,'2025-01-21 11:26:57',150.00,2,2),(11,'2025-01-21 11:27:49',300.00,2,2);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-01-25 23:39:51
