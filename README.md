# 水族箱
### 1.結構 編號1~5號魚
- 編號 int
- 名稱	char name[20]
- 顏色 char
- 體型 float 5-15cm	每餵食兩次+0.5
- 心情 int 1-5 (難過~開心)	互動可+1,每做三次動作使其他魚的心情-1
- 飢餓度 int 0-5 初始值為3，等於0時生命-1，每做四次動作-1
- 生命 int 0-5	為0時死亡 每餵食兩次+0.5，飢餓為0或心情為1時-1
### 2.可呼叫飼養中的魚	(檔案儲存、讀入)
### 3.隨時顯示魚的狀態 (主選單選項3，檢視資料)
### 4.可和寵物互動 (餵食、互動)
### 5.起始5個飼料，可於互動中隨機取得額外飼料
### 6.各種事項用選單輸入

## 起始畫面
![image](https://github.com/user-attachments/assets/6b95463b-e106-42e6-9824-0459a2a60550)
<br/>
<br/>**輸入選單對應號碼執行動作，起手將有五隻魚**<br/>
<br/>
![image](https://github.com/user-attachments/assets/be4a255a-8eb6-4429-9249-0db1472360da)
<br/>
<br/>**藉由動作選單執行動作**<br/>
<br/>
![image](https://github.com/user-attachments/assets/b7cc2b03-146b-4414-8ad8-edf9c2f73716)
<br/><br/>**可指定餵食的對象，餵食會增加體型和生命值**<br/><br/>
![image](https://github.com/user-attachments/assets/8875b90c-576b-40db-b4bd-f3a5cca1111a)
<br/><br/>**也能和魚進行互動，讓魚開心並機率取得飼料**<br/><br/>
![image](https://github.com/user-attachments/assets/b13d6ff8-530a-4811-8393-19ce9d31eb56)
<br/><br/>**若執行四次動作，連續四次都沒被餵食的魚飢餓度會下降**<br/><br/>
![image](https://github.com/user-attachments/assets/1fcad9fd-3c67-41b7-8118-a2d8c4d707a0)
<br/><br/>**心情不佳/飢餓度不足時，魚的生命值會下降，最後死亡**<br/><br/>
![image](https://github.com/user-attachments/assets/ad2d7d75-63a7-4cde-9c03-717319b5d11d)





