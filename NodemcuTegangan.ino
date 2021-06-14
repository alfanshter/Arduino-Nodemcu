    
    String dataIn;
    String dt[10];
    int i;
    boolean parsing=false;
    
    void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }
    }
    
    void loop() {
    if (Serial.available()) {
      delay(10);
        char inChar = (char)Serial.read();
        dataIn += inChar;
        if (inChar == '\n') {
        parsing = true;
        
    }
    
    }
    
    if(parsing){
        parsingData();
        parsing=false;
        dataIn="";
      }
    }
    
    
    void parsingData(){
    int j=0;
     
    //kirim data yang telah diterima sebelumnya
    Serial.print("data masuk : ");
    Serial.print(dataIn);
     
    //inisialisasi variabel, (reset isi variabel)
    dt[j]="";
    //proses parsing data
    for(i=1;i<dataIn.length();i++){
    //pengecekan tiap karakter dengan karakter (#) dan (,)
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
    //increment variabel j, digunakan untuk merubah index array penampung
    j++;
    dt[j]="";       //inisialisasi variabel array dt[j]
    }
    else
    {
    //proses tampung data saat pengecekan karakter selesai.
    dt[j] = dt[j] + dataIn[i];
    }
    }
     
    //kirim data hasil parsing
    Serial.print("data Tegangan : ");
    Serial.println(dt[0]);
    Serial.print("data Arus: ");
    Serial.println(dt[1].toFloat());
    Serial.print("data 3 : ");
    Serial.println(dt[2].toFloat());
    Serial.print("data 4 : ");
    Serial.println(dt[3].toInt());
    Serial.print("\n\n");
    }
    
