import requests
import threading
import json

#192.168.11.12 Lコース
#192.168.11.13 Rコース

class CompetitionSystem:
    """
    競技システム用の送受信シングルトンクラス
    """
    _instance = None
    _lock = threading.Lock()

    def __new__(cls, *args, **kwargs):
        with cls._lock:
            if not cls._instance:
                cls._instance = super(CompetitionSystem, cls).__new__(cls)
                print("[ 競技システム ]競技システム初回起動")
                #cls.setCourse('test')
        return cls._instance

    def setCourse(self, course = 'test'):
        """
        courseにはRコースを'R',Lコースは'L'を指定してください。その他はtest用のipv4が設定されます。
        """
        self.__course = course #rかl
        self.__Lipv4 = '192.168.11.12'
        self.__Ripv4 = '192.168.11.13'
        self.__Testipv4 = '192.168.100.1'
        self.__offline = '0,0,0,0'

        self.__IoTdata = []
        # base url
        if(self.__course in ['L', 'l']):
            ipv4 = self.__Lipv4
        elif(self.__course in ['R', 'r']):
            ipv4 = self.__Ripv4
        elif(self.__course in ['offline', 'r']):
            ipv4 = self.__offline
        else:
            ipv4 = self.__Testipv4

        self.__ipv4 = ipv4
        self.__snap_url = f'http://{self.__ipv4}/snap'
        self.__IoT_url = f'http://{self.__ipv4}/train'
        print(f"[ 競技システム ] {course}コース用のipv4 \"{self.__ipv4}\"を設定しました。")

        #teamID 任意のIDを設定します
        self.__id_parameter = 4 

    def snap(self, image_path):
        """
        ロボコンスナップをimage_pathを指定して送信する。\n
        返り値:\n
            成功 -> True\n
            失敗 -> False
        """
        if(self.__ipv4 == self.__offline):
            return True        

        # リクエストヘッダー
        headers = {'Content-Type': 'image/png'}
        
        # 完全なURLを生成
        url = f'{self.__snap_url}?id={self.__id_parameter}'

        # PNG画像ファイルを読み取り、HTTP POSTリクエストを送信
        with open(image_path, 'rb') as file:
            response = requests.post(url, headers=headers, data=file)
        
        # レスポンスを処理する（必要に応じて）
        if response.status_code == 201:
            print('[ snap ]リクエストが成功しました')
            return True
            # レスポンスの内容を表示する場合は、以下を使用します
            # print(response.text)
        else:
            print(f'[ snap ]リクエストが失敗しました。ステータスコード: {response.status_code}')
        return False

    def IoT_SET(self, pwm_value:int):
        """
        IoT列車の速度の操作を行い、pwm_value値に変更する。 \n
        pwm_value: int \n
        返り値:\n
            成功 -> True\n
            失敗 -> False
        """
        if(self.__ipv4 == self.__offline):
            return True

        payload = {"pwm": pwm_value}
        response = requests.put(self.__IoT_url, params=payload)

        if response.status_code == 200:
            return True
        else:
            print(f'[ IoT_SET ]リクエストが失敗しました。ステータスコード: {response.status_code}')
        return False

    # データの数値変換関数
    def __convert_to_float(self, data):
        if data is None:
            raise ValueError(":各種データの情報がありません")
        try:
            return float(data)
        except ValueError:
            raise ValueError(f":{data}をFloat型に解決できません")

    def loadData(self, path):
        with open(path, "r") as f:
            self.__IoTdata = json.load(f)

    def IoT_GET(self):
        """
        IoT列車の情報を取得する。\n
        格納情報はapiリファレンスを参照
        返り値:\n
            成功 -> センサデータ(辞書型)\n
            失敗 -> False
        """
        if(self.__ipv4 == self.__offline):
            try:
                ret_data = self.__IoTdata.pop(0)
                return ret_data
            except:
                print("データ終了")
                return False

        # GETリクエストを送信
        response = requests.get(self.__IoT_url)

        # レスポンスが成功した場合、JSONデータを解析する
        if response.status_code == 200:
            data = response.json()

            if data is None:
                print("[ IoT_GET ]リクエストデータの情報がありません")
            else:
                try:
                    # 数値に変換
                    accel_x = self.__convert_to_float(data['accel']['x'])
                    accel_y = self.__convert_to_float(data['accel']['y'])
                    accel_z = self.__convert_to_float(data['accel']['z'])

                    gyro_x = self.__convert_to_float(data['gyro']['x'])
                    gyro_y = self.__convert_to_float(data['gyro']['y'])
                    gyro_z = self.__convert_to_float(data['gyro']['z'])

                    volt = self.__convert_to_float(data['volt'])

                    print(end=f"[Accel: X={accel_x}, Y={accel_y}, Z={accel_z}], ")
                    print(end=f"[Gyro: X={gyro_x}, Y={gyro_y}, Z={gyro_z}], ")
                    print(end=f"[Volt: {volt}]\n")

                    # 辞書型に変換
                    ret_data = {
                        'accel': {
                            'x': accel_x,
                            'y': accel_y,
                            'z': accel_z
                        },
                        'gyro': {
                            'x': gyro_x,
                            'y': gyro_y,
                            'z': gyro_z
                        },
                        'volt': volt
                    }

                    return ret_data

                except (KeyError, ValueError) as e:
                    print(f"[ IoT_GET ]処理データエラー: {e}")

        else:
            print(f"[ IoT_GET ]リクエストが失敗しました。ステータスコード: {response.status_code}")
        return False


import time
if __name__ == "__main__":
    competitionSystem = CompetitionSystem()
    competitionSystem.setCourse('test')

    #competitionSystem.loadData('./IoT.json')

    #competitionSystem.snap('vga.png')
    competitionSystem.IoT_SET(30)
    li = []
    t = 100
    for i in range(t):
        li.append(competitionSystem.IoT_GET())
        time.sleep(50/1000)
    competitionSystem.IoT_SET(0)

    with open("IoT.json", "w") as f:
        json.dump(li, f, indent=4)