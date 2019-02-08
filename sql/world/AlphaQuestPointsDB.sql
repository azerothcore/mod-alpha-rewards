CREATE TABLE IF NOT EXISTS `alphaquestpoints` (
  `quest_id` int(10) NOT NULL,
  `points` int(10) DEFAULT NULL,
  `quest_title` varchar(255) NOT NULL,
  PRIMARY KEY (`quest_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `alphaquestpoints` (`quest_id`, `points`, `quest_title`) VALUES
	(24788, 3, 'Daily Heroic Random (1st)'),
	(24790, 1, 'Daily Normal Random (1st)');
	
