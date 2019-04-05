<?php
// ������ ��������� �������� ����������� ������ ��� �����������

// ������� �������� ��������� PHP, ����� � ESP �� �������� �������
header_remove();

$incoming_data = $_POST; // ����� - ������ �������� ��������� �������

function dumpRequest() // ������ ������ � ����
{
  $req_dump = print_r($_REQUEST,TRUE);
  $fp = fopen('request.log','a');
  if($fp !== FALSE)
  {
      fwrite($fp,"===================================================================\r\n");
      fwrite($fp,$req_dump);
      fwrite($fp, "\r\n");
      fclose($fp);
  }
}
// ����������������, ���� �� ����� ���� �� ���������� ������� !!!
dumpRequest();

/*

  �� ���� ��� ����� �������� �� ����� ���� ������!

  ������ ������������� ������� POST, �� ����������� ��������:
  
    k = (key) ���� ��� ������� � API
    s = (status) ������� ��������� ����������� (���� �� �����������)
    r = (report) - ���� ��� ���������� ����������� - �� ��� ����� �� ���������� �������
    c = (command) - �������� ������������� ����������� ������� (������ ���� r �����������!)
    
    ��� ��������� � ������� ���������� ����� ������� ��������� ���� � �����, � ����� ��������:
    
      d - ���� �����������, � ������� DD.MM.YYYY
      t - ����� �����������, � ������� HH:MM:SS
      z - �������� � ������� �� UTC, ��������, -180 ��� 120
    
  ������ ������ ������:
   
      1. ������ ������� ���������� ��������� [~] � ������������� ��������� ������ (\r\n)
      2. ����� �������� ��� ������������� ������� � �������, ����� �������������� - ������ #
      3. ����� ������� # ��� ����� �������, ������� ����� ���� ��� ������ ������� ������� (CTSET=...), 
         ��� � ��������� ����������� ���������� ��������������� �������.
      4. � ������, ���� ������������ ���������� ������������� �������, �� ����� ��� ������ ���� ������ ?
      5. ���� ������������ ���������� ������������� �������, �� ��� ����� ��������� �������������� ���������, 
         ��������� ����� ������� ? (��������, ����� ������ ������ ��� ���������)
      6. �� ���������� ������ ������ � ���������� ������ ������ �������� ������ "[CMDEND]\r\n"
      
  ������� ������:
  
    [~]1234#CTSET=WATER|ON - ������� � ID � ������� 1234, �������� - �������� �����
    [~]1235#?1 - ������� � ID � ������� 1235, �������� - ������� ��� ����
    [~]1236#?7?2 - ������� � ID � ������� 1236, �������� - �������� ����� �� ������� ������
    
    
    ������ ���������� ��������������� ������:
    
      1 - ������� ��� ����
      2 - ������� ��� ����
      3 - ������� ����������� ����
      4 - ������� ����������� ����
      5 - �������� ����� �� ���� �������
      6 - ��������� ����� �� ���� �������
      7 - �������� ����� �� ����������� ������
      8 - ��������� ����� �� ����������� ������
      9 - �������� ��������
      10 - ��������� ��������
      11 - �������� ���
      12 - ��������� ���
      
   ����� �������� ������� � ��������� ���������� ����������� ������, ��������� ��� ������������� ����������� �������.
   ������ ������ �������� ������� ��� �����������, ������ ���� �� ������� ����� �� ����������� � � �������� ����������.
    
*/

  $END_OF_COMMANDS = "[CMDEND]\r\n";

  // �������� �������
  $sample_commands = array(
    "[~]0000#CTSET=LIGHT|ON", // �������� ��������
    "[~]1111#?1", // ������� ��� ����
    "[~]2222#?7?2" // �������� ����� �� ������� ������
    
  );
  
  function isUserValid($key)
  {
    // ��� ���������, ���� �� ����� ���� � ��
    return true;
  }
  
  if(isset($incoming_data['k']) && isUserValid($incoming_data['k']) ) // ������ ���� ������� ���� � �� ����� ������ ������������
  {
  
         // ��������� - �� ��������� �� ������ ���������� �������?
         if(isset($incoming_data['r']))
         {
          // ��������� ������ ���������� �������, �������� ������������� ������� � �������� �, ��� �����������
          $command_identifier = @$incoming_data['c'];
          // ��� �������� ������� ��� ����������� � �� ��� ���� $_POST['k'] � $command_identifier
         }
         else // ��������� ������ ������ �� ����������
         {
        
            // ����� ������� ������� �� ��, ���� - ������ ����� ������ �������� ������
            foreach($sample_commands as $k => $v)
            {
              echo $v . "\r\n";
            }
        } // else
  
  }
  
  echo $END_OF_COMMANDS;

?>