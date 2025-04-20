# Stereo Görüntü İşleme Uygulaması

Bu uygulama, stereo görüntü çiftlerinden disparite haritaları oluşturmak için geliştirilmiş bir Qt tabanlı masaüstü uygulamasıdır.

## 🚀 Özellikler

- **Görüntü İşleme**
  - Sol ve sağ stereo görüntü çiftlerini yükleme
  - Ground truth (gerçek) disparite haritası yükleme
  - Çeşitli disparite hesaplama yöntemleri:
    - SAD (Sum of Absolute Differences)
    - SSD (Sum of Squared Differences)
    - ZNCC (Zero-Normalized Cross Correlation)

- **Performans Optimizasyonları**
  - Çoklu iş parçacığı (multi-threading) desteği
  - Optimize edilmiş hesaplama algoritmaları
  - Paralel işleme yetenekleri

- **Analiz ve Değerlendirme**
  - Hesaplanan disparite haritasını kaydetme
  - Ground truth ile karşılaştırma
  - SSD ve SAD tabanlı doğruluk ölçümleri
  - Sonuçların görsel ve sayısal analizi

## 🛠️ Gereksinimler

- Qt 5.x veya üzeri
- C++11 veya üzeri destekleyen bir derleyici
- CMake 3.x veya üzeri

## 📦 Kurulum

1. Projeyi klonlayın:
```bash
git clone [https://github.com/Looqs/StereoDisparityApp.git]
```

2. Build klasörü oluşturun:
Qt Creator ile olusturabilirsiniz.
```bash
mkdir build
cd build
```

3. CMake ile projeyi yapılandırın:
```bash
cmake ..
```

4. Projeyi derleyin:
```bash
cmake --build .
```

## 💻 Kullanım

1. Uygulamayı başlatın
2. "Sol Resmi Yükle" butonu ile sol görüntüyü yükleyin
3. "Sağ Resmi Yükle" butonu ile sağ görüntüyü yükleyin
4. Disparite hesaplama yöntemini seçin (SAD, SSD veya ZNCC)
5. "Disparity Hesapla" butonuna tıklayarak disparite haritasını oluşturun
6. İsterseniz "Gerçek Disparity Resmini Yükle" ile gerçek disparite haritasını yükleyin

## 🔧 Teknik Detaylar

### Disparite Hesaplama Yöntemleri

- **SAD (Sum of Absolute Differences)**
  - Piksel farklarının mutlak değerlerinin toplamını kullanır
  - Hızlı hesaplama, orta düzey doğruluk

- **SSD (Sum of Squared Differences)**
  - Piksel farklarının karelerinin toplamını kullanır
  - Yüksek doğruluk, daha yoğun hesaplama

- **ZNCC (Zero-Normalized Cross Correlation)**
  - Normalize edilmiş çapraz korelasyon kullanır
  - En yüksek doğruluk, en yoğun hesaplama

### Performans Optimizasyonları

- Çoklu iş parçacığı işleme ile paralel hesaplama
- Optimize edilmiş algoritma implementasyonları
- Bellek yönetimi optimizasyonları
