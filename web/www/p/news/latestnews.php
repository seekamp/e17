<?php
require_once 'p/news/class.news.php';

setlocale(LC_ALL, 'en_EN');

$news = new news;
$list = $news->get(2);
foreach($list as $new)
{
   if (($new = $news->read_content($new)) !== NULL)
   {
     echo "<p><a href='p.php?p=news/show&l=".$_GET['l']."&news_id=$new[id]'>".$new['title']."</a> - <em>".$new['date']."</em></p>";
     echo "<p>".$new['content']."</p>\n";
   }



}
echo "<p align='right'><a href='p.php?p=news&l=".$_GET['l']."' title='News'>More news ... </a></p>";
?>

