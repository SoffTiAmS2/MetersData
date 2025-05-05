Дулисов С. Р.
### Диаграмма Классов (UML)

```mermaid
classDiagram
    class FileHandler {
        +loadFromFile(path: string): MeterList
        +saveToFile(path: string, data: MeterList)
        -detectFormat(path: string): FileFormat
        -stream: FileStream
    }
    class FileStream {
        +openRead(path: string): InputStream
        +openWrite(path: string): OutputStream
        +close()
        -handle: FileHandle
    }

    class IFileFormat {
        <<interface>>
        +parse(input: QTextStream): MeterList
        +serialize(data: MeterList): QString
    }
    class TxtFormat {
        +parse(input: QTextStream): MeterList override
        +serialize(data: MeterList): QString override
        -formatMeter(meter: AbstractMeter*): QString
        -parser: MeterParser
    }
    class CsvFormat {
        +parse(input: QTextStream): MeterList override
        +serialize(data: MeterList): QString override
        -formatMeter(meter: AbstractMeter*): QString
        -parser: MeterParser
    }

    class MeterParser {
        +parse(input: string): unique_ptr~AbstractMeter~
        -factory: MeterFactory
        -splitter: ISpliter
        -dateParser: DateParser
        -valueParser: ValueParser
    }

    class ISpliter {
        <<interface>>
        +virtual split(input: string) const: vector~string~
    }
    class StringSplitter {
        +split(input: string) const: vector~string~
    }
    class CsvSplitter {
        +split(input: string) const: vector~string~
    }

    class Validator {
        <<Utils>>
        +static isValidDateFormat(dateStr: string): bool
        +static isValidDateValues(year: int, month: int, day: int): bool
        +static isValidValue(valueStr: string): bool
        +static dateRegex(): regex
        +static valueRegex(): regex
    }

    class DateParser {
        +parse(input: string): Date
    }

    class ValueParser {
        +parse(input: string): float
    }

    class MeterFactory {
        +createMeter(type: string, date: Date, value: float, param: string): unique_ptr~AbstractMeter~
        -valueParser: ValueParser
    }

    class AbstractMeter {
        <<abstract>>
        +AbstractMeter(date: Date, value: float)
        +getDate(): Date&
        +getValue(): float
        +toString(): string
        #date: Date
        #value: float
    }

    class ElectricityMeter {
        +ElectricityMeter(date: Date, value: float, voltage: float)
        +getVoltage(): float
        +toString(): string
        -voltage: float
    }

    class WaterMeter {
        +WaterMeter(date: Date, value: float, isHot: bool)
        +isHot(): bool
        +toString(): string
        -isHot: bool
    }

    class GasMeter {
        +GasMeter(date: Date, value: float, serialNumber: string)
        +getSerialNumber(): string
        +toString(): string
        -serialNumber: string
    }

    class MeterList {
        +addMeter(meter: unique_ptr~AbstractMeter~): void
        +removeMeter(index: size_t): void
        +clear(): void
        +getMeters(): vector~unique_ptr~AbstractMeter~~&
        +size(): size_t
        +empty(): bool
        -meters: vector~unique_ptr~AbstractMeter~~
    }

    class MeterController {
        +loadFromFile(path: QString)
        +saveToFile(path: QString)
        +getMeters(): const MeterList&
        -meters: MeterList
        -fileHandler: FileHandler
    }

    class MainWindow {
        +displayMeters(list: MeterList)
        +onAddMeter()
        +onLoadFromFile()
        +onSaveToFile()
        -ui: QWidget
        -meterView: MeterListView
        -controller: MeterController
    }

    class MeterListView {
        +updateView(list: MeterList)
        -table: QTableWidget
    }

    class AbstractMeter {
        <<abstract>>
        +AbstractMeter(date: const Date&, value: float)
        +getDate(): const Date&
        +getValue(): float
        +toString(): string
        #date: Date
        #value: float
    }

    class ElectricityMeter {
        +ElectricityMeter(date: const Date&, value: float, voltage: float)
        +getVoltage(): float
        +toString(): string
        -voltage: float
    }

    class WaterMeter {
        +WaterMeter(date: const Date&, value: float, isHot: bool)
        +isHot(): bool
        +toString(): string
        -isHot: bool
    }

    class GasMeter {
        +GasMeter(date: const Date&, value: float, serialNumber: const string&)
        +getSerialNumber(): const string&
        +toString(): string
        -serialNumber: string
    }

    class Date {
        +Date(year: int, month: int, day: int)
        +getYear(): int
        +getMonth(): int
        +getDay(): int
        +toString(): string
        -year: int
        -month: int
        -day: int
    }


    FileHandler --> FileStream : использует
    FileHandler --> IFileFormat : выбирает реализацию
    IFileFormat <|.. TxtFormat : реализует
    IFileFormat <|.. CsvFormat : реализует
    TxtFormat --> MeterParser : использует
    CsvFormat --> MeterParser : использует
    MeterParser --> ISpliter : имеет
    MeterParser --> StringSplitter : может использовать
    MeterParser --> CsvSplitter : может использовать
    MeterParser --> DateParser : использует
    MeterParser --> ValueParser : использует
    DateParser ..> Validator : использует статические методы
    ValueParser ..> Validator : использует статические методы
    MeterParser --> MeterFactory : использует
    MeterFactory --> ValueParser : использует
    AbstractMeter <|-- ElectricityMeter : наследуется
    AbstractMeter <|-- WaterMeter : наследуется
    AbstractMeter <|-- GasMeter : наследуется
    MeterList *-- AbstractMeter : содержит
    MeterController --> MeterList : управляет
    MeterController --> FileHandler : использует
    MainWindow --> MeterController : использует
    MainWindow --> MeterListView : использует
    MeterListView --> MeterList : отображает

    MeterFactory --> AbstractMeter : создает

    DateParser -->  Date : создает

    AbstractMeter --> Date : содержит

    %% ==== Комментарии ====
    note for MeterParser "Парсит строку в счётчик. Хранит фабрику и вспомогательные парсеры."
    note for MeterFactory "Создаёт экземпляры счётчиков в зависимости от типа и параметров."
    note for Validator "Набор статических методов для валидации строки, значений, дат и форматов."
```