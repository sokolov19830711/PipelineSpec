function Project()
{
    this.type = "project";
    this.properties = {
        projID          : "<не задано>",
        fullName        : "<не задано>",
        customer        : "<не задано>",
        developer       : "<не задано>",
        check           : "<не задано>",
        head            : "<не задано>",
        stage           : "П",
        ctrl            : "<не задано>",
        CPE             : "<не задано>",
        date            : "<не задано>",
        mountMark       : "<не задано>",
        insulationMark   : "<не задано>",
        T_min_air       : 0,
    };

    this.ui = function () {return Project.ui};

    this.projectFileName = "";
    this.sectionList = [];
    this.currentSectionIndex = -1;
}

Project.ui = {
    table : [
        {propertyName : "projID", caption : "<i>&nbsp;Шифр<i/>", widgetType : "lineEdit"},
        {propertyName : "fullName", caption : "<i>&nbsp;Наименование<i/>", widgetType : "lineEdit"},
        {propertyName : "customer", caption : "<i>&nbsp;Заказчик<i/>", widgetType : "lineEdit"},
        {propertyName : "developer", caption : "<i>&nbsp;Разработал<i/>", widgetType : "lineEdit"},
        {propertyName : "check", caption : "<i>&nbsp;Проверил<i/>", widgetType : "lineEdit"},
        {propertyName : "head", caption : "<i>&nbsp;Нач. отд.<i/>", widgetType : "lineEdit"},
        {propertyName : "stage", caption : "<i>&nbsp;Стадия<i/>", widgetType : "comboBox", valueList : function(){return ["П", "Р"]}},
        {propertyName : "ctrl", caption : "<i>&nbsp;Н. контр.<i/>", widgetType : "lineEdit"},
        {propertyName : "CPE", caption : "<i>&nbsp;ГИП<i/>", widgetType : "lineEdit"},
        {propertyName : "date", caption : "<i>&nbsp;Дата<i/>", widgetType : "lineEdit"},
        {propertyName : "mountMark", caption : "<i>&nbsp;Марка комплекта ТМ<i/>", widgetType : "lineEdit"},
        {propertyName : "insulationMark", caption : "<i>&nbsp;Марка комплекта ТИ<i/>", widgetType : "lineEdit"},
        {propertyName : "T_min_air", caption : "<i>&nbsp;Мин. температура воздуха<i/>", widgetType : "spinBox", decimals : 0, maximum : 60, minimum : -60}
           ]

};

function restoreItemTypes (sectionList)
{
    for (var i = 0; i < sectionList.length; i++)
    {
        sectionList[i].__proto__ = this[sectionList[i].type];
        for (var j = 0; j < sectionList[i].itemList.length; j++)
        {
            sectionList[i].itemList[j].__proto__ = this[sectionList[i].itemList[j].type];
        }
    }
}


var project = new Project();
