-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 15, 2023 at 08:40 AM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.0.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `posttest`
--

-- --------------------------------------------------------

--
-- Table structure for table `posttest`
--

CREATE TABLE `posttest` (
  `id` int(2) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `role` enum('user','admin') NOT NULL,
  `user_image` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `posttest`
--

INSERT INTO `posttest` (`id`, `username`, `password`, `role`, `user_image`) VALUES
(1, 'admin', 'admin', 'admin', ''),
(44, 'adada', 'adawdaw', 'user', '2023-11-15 adada.jpeg'),
(45, 'hai', '123', 'user', '2023-11-15 hai.png'),
(46, 'test', 'test', 'user', '2023-11-15 test.webp'),
(47, 'ada', 'ada', 'user', ''),
(48, 'halo', '123', 'user', ''),
(49, 'papa', '123', 'user', ''),
(50, 'a', '123', 'user', ''),
(51, 'pepe', '123', 'user', '');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `posttest`
--
ALTER TABLE `posttest`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `posttest`
--
ALTER TABLE `posttest`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=52;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
