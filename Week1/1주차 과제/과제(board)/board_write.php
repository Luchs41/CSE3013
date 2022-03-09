<?
	//게시판 쓰기 페이지 제목
	echo("<meta charset='utf-8'>");
	echo("<b>게시판 쓰기</b><br><br>");
	//내용을 받을 글상자 생성 및 등록하기, 다시기입 버튼 생성
	echo("
			<form name='input' method='POST' action='$PHP_SELF'>
			<textarea name='text' rows=20 cols=100></textarea><br><br>
			<input type='submit' value='등록하기'>
			<input type='reset' value='다시기입'>
			</form>
		");

	//내용 입력받기
	$string = $_POST['text'];
	//입력받은 글이 있다면 if문으로 들어감
	if($string)
	{
		//data.txt에 입력받은 내용을 저장함
		$fp = fopen("data.txt", "w");
		fwrite($fp, "$string", filesize("data.txt"));
		fclose($fp);
		//저장 후 board_main.php으로 자동적으로 돌아감
		echo("<meta http-equiv='Refresh' content='0.1; URL=board_main.php'>");
	}
	//되돌아 가기를 누르면 board_main.php로 돌아가는 링크 생성
	echo("<a href='board_main.php'>되돌아 가기<br></a>");
?>