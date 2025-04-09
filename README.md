# Stereo Disparity App

Bu uygulama, stereo görüntüler arasındaki derinlik farkını hesaplamak için çeşitli algoritmalar kullanır. Kullanıcı, farklı algoritmalar ve pencere boyutları seçerek derinlik haritaları oluşturabilir.

## Özellikler

- **Görüntü Yükleme**: Sol ve sağ görüntüleri yükleyin.
- **Derinlik Hesaplama**: SAD, SSD ve ZNCC algoritmalarını kullanarak derinlik haritaları oluşturun.
- **Pencere Boyutu Ayarlama**: Derinlik hesaplaması için pencere boyutunu belirleyin.

## Kullanım

1. **Görüntüleri Yükleyin**: "Load Images" butonuna tıklayarak sol ve sağ görüntüleri yükleyin.
2. **Algoritma Seçin**: Kullanmak istediğiniz algoritmayı seçin (SAD, SSD veya ZNCC).
3. **Pencere Boyutunu Ayarlayın**: Pencere boyutunu girin.
4. **Hesapla**: "Compute Disparity" butonuna tıklayarak derinlik haritasını hesaplayın.

## Gereksinimler

- OpenCV
- Qt

## Kurulum

1. Gerekli kütüphaneleri yükleyin:
   ```bash
   sudo apt-get install libopencv-dev
   sudo apt-get install qt5-default
   ```

2. Projeyi klonlayın:
   ```bash
   git clone <repository-url>
   cd StereoDisparityApp
   ```

3. Uygulamayı derleyin ve çalıştırın:
   ```bash
   qmake
   make
   ./StereoDisparityApp
   ```

## Katkıda Bulunma

Katkıda bulunmak isterseniz, lütfen bir pull request gönderin veya bir issue açın.

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır.