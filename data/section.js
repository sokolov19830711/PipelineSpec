function Section()
{
    this.ui = function () {return Section.ui};
    this.calc = function ()
    {
        var curr = this.properties;

        //---Выбор материала трубопровода-------------------------------------------------

        if ((curr.T1 < -40 || currentProject.properties.T_min_air < -40) && !curr.isInsulated) curr.material = "09Г2С";
        else curr.material = "сталь 20";

        //---P_usl------------------------------------------------------------------------

        if (((curr.P_ras <= 16) && (curr.T_max <= 200)) ||
                ((curr.P_ras <= 14) && (curr.T_max <= 250)) ||
                ((curr.P_ras <= 12) && (curr.T_max <= 300)) ||
                ((curr.P_ras <= 11) && (curr.T_max <= 350)) ||
                ((curr.P_ras <= 9) && (curr.T_max <= 400)) ||
                ((curr.P_ras <= 8) && (curr.T_max <= 425)) ||
                ((curr.P_ras <= 7) && (curr.T_max <= 435)) ||
                ((curr.P_ras <= 6.2) && (curr.T_max <= 445)) ||
                ((curr.P_ras <= 5.7) && (curr.T_max <= 455)))
        {
            curr.P_usl = 16;
        }

        else if (((curr.P_ras <= 40) && (curr.T_max <= 200)) ||
                ((curr.P_ras <= 35) && (curr.T_max <= 250)) ||
                ((curr.P_ras <= 30) && (curr.T_max <= 300)) ||
                ((curr.P_ras <= 26) && (curr.T_max <= 350)) ||
                ((curr.P_ras <= 23) && (curr.T_max <= 400)) ||
                ((curr.P_ras <= 20) && (curr.T_max <= 425)) ||
                ((curr.P_ras <= 18) && (curr.T_max <= 435)) ||
                ((curr.P_ras <= 16) && (curr.T_max <= 445)) ||
                ((curr.P_ras <= 14) && (curr.T_max <= 455)))
        {
            curr.P_usl = 40;
        }

        else if (((curr.P_ras <= 63) && (curr.T_max <= 200)) ||
                ((curr.P_ras <= 54) && (curr.T_max <= 250)) ||
                ((curr.P_ras <= 48) && (curr.T_max <= 300)) ||
                ((curr.P_ras <= 40) && (curr.T_max <= 350)) ||
                ((curr.P_ras <= 37) && (curr.T_max <= 400)) ||
                ((curr.P_ras <= 32) && (curr.T_max <= 425)) ||
                ((curr.P_ras <= 28) && (curr.T_max <= 435)) ||
                ((curr.P_ras <= 25) && (curr.T_max <= 445)) ||
                ((curr.P_ras <= 23) && (curr.T_max <= 455)))
        {
            curr.P_usl = 63;
        }

        else curr.P_usl = 100;

        //---P_pro---------------------------------------------------------------------------

        var sigma = 1;
        if (curr.material === "сталь 20")
        {
            if (curr.T_max >=50 && curr.T_max < 100) sigma = interp(curr.T_max,       50,  100, 1.02, 1.04);
            else if (curr.T_max >=100 && curr.T_max < 150) sigma = interp(curr.T_max, 100, 150, 1.04, 1.06);
            else if (curr.T_max >=150 && curr.T_max < 200) sigma = interp(curr.T_max, 150, 200, 1.06, 1.08);
            else if (curr.T_max >=200 && curr.T_max < 250) sigma = interp(curr.T_max, 200, 250, 1.08, 1.11);
            else if (curr.T_max >=250 && curr.T_max < 300) sigma = interp(curr.T_max, 250, 300, 1.11, 1.24);
            else if (curr.T_max >=300 && curr.T_max < 350) sigma = interp(curr.T_max, 300, 350, 1.24, 1.39);
            else if (curr.T_max >=350 && curr.T_max < 400) sigma = interp(curr.T_max, 350, 400, 1.39, 1.6);
            else if (curr.T_max >=400 && curr.T_max < 450) sigma = interp(curr.T_max, 400, 450, 1.6,  2.4);
            else if (curr.T_max < 50) sigma = 1;
        }
        else
        {
            if (curr.T_max >=50 && curr.T_max < 100) sigma = interp(curr.T_max,       50,  100, 1.04, 1.14);
            else if (curr.T_max >=100 && curr.T_max < 150) sigma = interp(curr.T_max, 100, 150, 1.14, 1.19);
            else if (curr.T_max >=150 && curr.T_max < 200) sigma = interp(curr.T_max, 150, 200, 1.19, 1.24);
            else if (curr.T_max >=200 && curr.T_max < 250) sigma = interp(curr.T_max, 200, 250, 1.24, 1.26);
            else if (curr.T_max >=250 && curr.T_max < 300) sigma = interp(curr.T_max, 250, 300, 1.26, 1.33);
            else if (curr.T_max >=300 && curr.T_max < 350) sigma = interp(curr.T_max, 300, 350, 1.33, 1.45);
            else if (curr.T_max >=350 && curr.T_max < 400) sigma = interp(curr.T_max, 350, 400, 1.45, 1.76);
            else if (curr.T_max >=400 && curr.T_max < 450) sigma = interp(curr.T_max, 400, 450, 1.76, 2.76);
            else if (curr.T_max < 50) sigma = 1;
        }

        curr.P_pro = curr.P_ras * 1.25 * sigma;
        if ((curr.P_ras <= 5) && (curr.P_pro < 2)) curr.P_pro = 2;
        if ((curr.P_ras > 5) && (curr.P_pro < 8)) curr.P_pro = 8;

        ///---P_plo------------------------------------------------------------------------------------------------

        if (curr.P_rab > 2) curr.P_plo = curr.P_rab;
        else curr.P_plo = 2;

        //---P_ger-------------------------------------------------------------------------------------------------


        if ((curr.group === "Аа") ||
                (curr.group === "Аб") ||
                (curr.group === "Ба") ||
                (curr.group === "Бб") ||
                (curr.group === "Бв"))
        {
            if (curr.P_rab > 2) curr.P_ger = curr.P_rab;
            else curr.P_ger = 2;

            if ((curr.group === "Аа") || (curr.group === "Аб")) curr.dP = curr.P_ger * 0.001;
            else curr.dP = curr.P_ger * 0.002;
        }
        else
        {
            curr.P_ger = 0;
            curr.dP = 0;
        }

        //---Category----------------------------------------------------------------------------------------------

        if (curr.group === "В")
        {
            if ((curr.T1 < -40) || (currentProject.properties.T_min_air < -40 && !curr.isInsulated)) curr.category = "I";
            else if ((curr.P_ras > 63) || (curr.T_max > 350)) curr.category = "II";
            else if ((curr.P_ras > 25) || (curr.T_max > 250)) curr.category = "III";
            else if ((curr.P_ras > 16) || (curr.T_max > 120)) curr.category = "IV";
            else curr.category = "V";
        }

        else if (curr.group === "Аа") curr.category = "I";

        else if (curr.group === "Аб")
        {
            if ((curr.P_ras > 25) || (curr.T_max > 300) || (curr.T1 < -40)) curr.category = "I";
            else curr.category = "II";
        }

        else if (curr.group === "Ба")
        {
            if ((curr.P_ras > 25) || (curr.T_max > 300) || (curr.T1 < -40)) curr.category = "I";
            else curr.category = "II";
        }

        else if (curr.group === "Бб")
        {
            if ((curr.P_ras > 25) || (curr.T_max > 300) || (curr.T1 < -40)) curr.category = "I";
            else if ((curr.P_ras > 16) || (curr.T_max > 120)) curr.category = "II";
            else curr.category = "III";
        }

        else if (curr.group === "Бв")
        {
            if ((curr.P_ras > 63) || (curr.T_max > 350) || (curr.T1 < -40)) curr.category = "I";
            else if ((curr.P_ras > 25) || (curr.T_max > 250)) curr.category = "II";
            else if ((curr.P_ras > 16) || (curr.T_max > 120)) curr.category = "III";
            else curr.category = "IV";
        }

        //---weldCtrl------------------------------------------------------------------------------

        if (curr.category === "I") curr.weldCtrl = 20;
        else if (curr.category === "II") curr.weldCtrl = 10;
        else if (curr.category === "III") curr.weldCtrl = 2;
        else if (curr.category === "IV") curr.weldCtrl = 1;
        else curr.weldCtrl = 0;
    }

}

function EmptySection()
{
    this.type = "section";
    this.properties = {
        sectionName     : "",        /*Обозначение участка трубопровода*/
        from            : "",
        to              : "",
        product         : "",
        group           : "",
        category        : "",
        material        : "",        /*Основной материал трубопровода
                                     (для расчета давления испытания на прочность, подстановки по умолчанию для труб и фиттингов)*/

        isSteam         : false,     /*Участок является трубопроводом пара или горячей воды (по ПБ 10-573-03)*/
        isFlare         : false,     /*Участок является факельным трубопроводом (по РД 08-200-98)*/

        P_usl           : 0,         /*Условное давление, кгс\см2*/
        P_rab           : 0,         /*Рабочее давление, кгс\см2*/
        P_rab_text      : "",        /*Рабочее давление, кгс\см2 (в текстовом виде)*/
        P_ras           : 0,         /*Расчетное давление, кгс\см2*/

        P_pro           : 0,         /*Давление испытания на прочность, кгс\см2*/
        P_plo           : 0,         /*Давление испытания на плотность, кгс\см2*/
        P_ger           : 0,         /*Давление испытания на герметичность, кгс\см2*/

        M_pro           : "-",       /*Метод испытания на прочность*/
        M_plo           : "-",       /*Метод испытания на плотность*/
        M_ger           : "-",       /*Метод испытания на герметичность*/

        dP              : 0,         /*Падение давления во время испытания, МПа*/
        t               : 24,         /*Время испытания, ч*/

        T1              : 0,         /*Нижний предел рабочей тепературы, С*/
        T2              : 0,         /*Верхний предел рабочей тепературы, С*/
        T_max           : 0,         /*Максимальная тепература, С*/

        weldCtrl        : 0,         /*Объем контроля сварных швов, %*/
        corr            : 0,         /*Скорость коррозии, мм/год*/
        workPeriod      : 0,         /*Срок службы, лет*/
        isInsulated     : false,     /*Изолированный трубопровод*/
        isHeated        : false,     /*Обогреваемый трубопровод*/
        insul_type      : "-",       /*Назначение изоляции*/
        isTherm         : false     /*Термообработка*/
    };

    this.itemList = [];
}

Section.categoryValueList = function(item)
{
    switch (item.properties["group"])
    {
    case "Аа":
        return ["I"];

    case "Аб":
    case "Ба":
        return ["I", "II"];

    case "Бб":
        return ["I", "II", "III"];

    case "Бв":
        return ["I", "II", "III", "IV"];

    case "В":
        return ["I", "II", "III", "IV", "V"];
    }
}

Section.ui = {
    table : [
        {propertyName : "sectionName", caption : "<i>&nbsp;Обозначение участка</i>", toolTip : "Обозначение участка",
            widgetType : "lineEdit"},
        {propertyName : "from", caption : "<i>&nbsp;ОТ</i>", toolTip : "Начало участка трубопровода",
            widgetType : "lineEdit"},
        {propertyName : "to", caption : "<i>&nbsp;ДО</i>", toolTip : "Конец участка трубопровода",
            widgetType : "lineEdit"},
        {propertyName : "product", caption : "<i>&nbsp;Наименование продукта</i>", toolTip : "Наименование транспортируемого продукта",
            widgetType : "lineEdit"},
        {propertyName : "group", caption : "<i>&nbsp;Группа</i>", toolTip : "Группа",
            widgetType : "comboBox", valueList : function(){return ["Аа", "Аб", "Ба", "Бб", "Бв", "В"]}},
        {propertyName : "category", caption : "<i>&nbsp;Категория</i>", toolTip : "Категория",
            widgetType : "comboBox", valueList : Section.categoryValueList},
        {propertyName : "material", caption : "<i>&nbsp;Материал трубопровода</i>", toolTip : "Основной материал трубопровода\n(для расчета давления испытания на прочность, подстановки по умолчанию для труб и фиттингов)",
            widgetType : "lineEdit"},

        {propertyName : "isSteam", caption : "<i>&nbsp;Трубопровод пара</i>", toolTip : "Участок является трубопроводом пара или горячей воды (по ПБ 10-573-03)",
            widgetType : "yesNoBox"},
        {propertyName : "isFlare", caption : "<i>&nbsp;Факельный трубопровод</i>", toolTip : "Участок является факельным трубопроводом (по РД 08-200-98)",
            widgetType : "yesNoBox"},


        {propertyName : "P_usl", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>усл</sub></b></i>", toolTip : "Условное&nbsp;давление, кгс&#047;см<sup>2</sup>",
            widgetType : "comboBox", valueList : function(){return ["16", "40", "63", "100"]}},
        {propertyName : "P_rab", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>раб</sub></b></i>", toolTip : "Рабочее&nbsp;давление, кгс&#047;см<sup>2</sup>",
            widgetType : "spinBox", decimals : 1, maximum : 100, minimum : 0},
        {propertyName : "P_rab_text", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>раб</sub></b></i> (текст)", toolTip : "Рабочее давление в текстовом виде",
            widgetType : "lineEdit"},
        {propertyName : "P_ras", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>расч</sub></b></i>", toolTip : "Расчетное&nbsp;давление, кгс&#047;см<sup>2</sup>",
            widgetType : "spinBox", decimals : 1, maximum : 100, minimum : 0},

        {propertyName : "P_pro", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>проч</sub></b></i>",  toolTip : "Давление испытания на прочность,&#010;кгс&#047;см<sup>2</sup>",
            widgetType : "spinBox", decimals : 1, maximum : 100, minimum : 0},
        {propertyName : "P_plo", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>плот</sub></b></i>",  toolTip : "Давление испытания на плотность,&#010;кгс&#047;см<sup>2</sup>",
            widgetType : "spinBox", decimals : 1, maximum : 100, minimum : 0},
        {propertyName : "P_ger", caption : "<i><b>&nbsp;&nbsp;&nbsp;P<sub>герм</sub></b></i>",  toolTip : "Давление испытания на герметичность,&#010;кгс&#047;см<sup>2</sup>",
            widgetType : "spinBox", decimals : 1, maximum : 100, minimum : 0},

        {propertyName : "M_pro", caption : "<i>&nbsp;Исп. на прочность</i>",  toolTip : "Метод испытания на прочность: Г - гидравлический; П - пневматический",
            widgetType : "comboBox", valueList : function(){return ["-", "Г", "П"]}},
        {propertyName : "M_plo", caption : "<i>&nbsp;Исп. на плотность</i>",  toolTip : "Метод испытания на плотность: Г - гидравлический; П - пневматический",
            widgetType : "comboBox", valueList : function(){return ["-", "Г", "П"]}},
        {propertyName : "M_ger", caption : "<i>&nbsp;Исп. на герметичность</i>",  toolTip : "Метод испытания на герметичность: Г - гидравлический; П - пневматический",
            widgetType : "comboBox", valueList : function(){return ["-", "Г", "П"]}},

        {propertyName : "dP", caption : "<i><b>&nbsp;&nbsp;&nbsp;&Delta;P<i><b>", toolTip : "Максимальное падение давления при испытании на герметичность, кгс&#047;см<sup>2</sup> в час",
            widgetType : "spinBox", decimals : 3, maximum : 0.1, minimum : 0, singleStep : 0.001},
        {propertyName : "t", caption : "<i><b>&nbsp;&nbsp;&nbsp;t(ч)<i><b>", toolTip : "Время испытания, ч",
            widgetType : "lineEdit"},


        {propertyName : "T1", caption : "<i><b>&nbsp;&nbsp;&nbsp;T<sub>нижн</sub></b></i>", toolTip : "Нижний предел рабочей тепературы, С<i>&deg;</i>",
            widgetType : "spinBox", decimals : 0, maximum : 300, minimum : -100},
        {propertyName : "T2", caption : "<i><b>&nbsp;&nbsp;&nbsp;T<sub>верх</sub></b></i>", toolTip : "Верхний предел рабочей тепературы, С<i>&deg;</i>",
            widgetType : "spinBox", decimals : 0, maximum : 300, minimum : -100},
        {propertyName : "T_max", caption : "<i><b>&nbsp;&nbsp;&nbsp;T<sub>max</sub></b></i>", toolTip : "Максимальная тепература, С<i>&deg;</i>",
            widgetType : "spinBox", decimals : 0, maximum : 300, minimum : -100},


        {propertyName : "weldCtrl", caption : "<i>&nbsp;Контроль сварных швов</i>", toolTip : "Объем контроля сварных швов, %",
            widgetType : "spinBox", decimals : 0, maximum : 100, minimum : 0},
        {propertyName : "corr", caption : "<i>&nbsp;Скорость коррозии</i>", toolTip : "Скорость коррозии материала трубопровода, мм в год",
            widgetType : "spinBox", decimals : 1, maximum : 0.5, minimum : 0, singleStep : 0.1},
        {propertyName : "workPeriod", caption : "<i>&nbsp;Скорость службы</i>", toolTip : "Скорость службы участка трубопровода, лет",
            widgetType : "spinBox", decimals : 0, maximum : 50, minimum : 0},

        {propertyName : "isInsulated", caption : "<i>&nbsp;Изолированный трубопровод</i>",
            widgetType : "yesNoBox"},
        {propertyName : "isHeated", caption : "<i>&nbsp;Обогреваемый трубопровод</i>",
            widgetType : "yesNoBox"},
        {propertyName : "insul_type", caption : "<i>&nbsp;Назначение изоляции</i>",  toolTip : "Назначение изоляции: А - уменьшение теплопотерь; В - предотвращение ожогов персонала; С - гидроизоляция",
            widgetType : "comboBox", valueList : function(){return ["-", "A", "B", "C"]}},
        {propertyName : "isTherm", caption : "<i>&nbsp;Термообработка</i>",
            widgetType : "yesNoBox"}
           ]

};


function interp(x, x1, x2, y1, y2)
{
    return (y1 + (y2 - y1) / (x2 - x1) * (x - x1));
}

var section = new Section();
