<?
	//파일을 열어 저장된 count 수를 변수에 저장
	$fp = fopen("counter.txt", "r");
	$count = fread($fp, filesize("counter.txt"));
	fclose($fp);
	//ip값이 쿠키로 설정되어있지 않다면 count 증가
	if (!$_COOKIE["ip"])
	{
		setcookie("ip", $_SERVER["REMOTE_ADDR"]);
		$count++;
	}
	//파일을 열어 증가된 count를 저장
	$fp = fopen("counter.txt", "w");
	fwrite($fp, "$count", strlen($count));
	fclose($fp);
	//count를 문자열 형태로 저장
	$string = (string)$count;
	echo("<meta charset='utf-8'>");
	echo("<font size=7>방문자 수 : </font>");
	//문자열 형태로 저장된 count를 한글자씩 불러와 그에 해당하는 이미지 파일로 출력
	for ( $i=0; $i<strlen($string); $i++)
	{
		$ch = substr($string,$i,1);
		echo("<img src=".$ch.".jpg>");
	}
?>