
byte addressRemote[5] = {'0', '0', '0', '0', '2'};

void radio_setup()
{  
  Radio.begin(addressRemote,10);  
}

void radio_write(struct SensorData data)
{
  Radio.write(addressRemote,data);
}


