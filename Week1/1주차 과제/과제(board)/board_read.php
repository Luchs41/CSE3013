<?
	//게시판 읽기 페이지 제목
	echo("<meta charset='utf-8'>");
	echo("<b>게시판 읽기</b><br><br>");
	//저장된 파일을 열어 변수에 내용을 저장
	$fp = fopen("data.txt", "r");

	$text = fread($fp, filesize("data.txt"));

	fclose($fp);
	//테이블을 생성해서 내용을 출력
	echo("
			<table border=1 width=600 height=120>
			<tr>
			<td valign='top'>
			$text
			</td></tr></table>
		");
	//되돌아 가기를 누르면 board_main.php로 돌아가는 링크 생성
	echo("<br><a href=board_main.php>되돌아 가기</a>");
?>