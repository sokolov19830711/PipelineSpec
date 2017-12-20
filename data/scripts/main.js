var projectList = [];
var currentProject;
var currentSection;
var currentItem;

function setupPropertyEditorUi(widget, item)
{
    widget.item = item;
    var table = widget.item.ui().table;
    widget.setRowCount(table.length);
    for (var i = 0; i < table.length; i++)
    {
        widget.setCellLabel(i, 0, table[i].caption, table[i].toolTip);
    }
}

function readPropertiesToEditor(widget, item)
{
    setupPropertyEditorUi(widget, item);
    var table = widget.item.ui().table;
    for (var i = 0; i < table.length; i++)
    {
        if (table[i].propertyName in item.properties)
        {
            switch (table[i].widgetType)
            {
//            case "checkBox":
//                widget.setInactiveCheckBox(i, 1, item.properties[table[i].propertyName]);
//                break;

            case "spinBox":
                widget.setCellText(i, 1, item.properties[table[i].propertyName]);
                widget.replaceFullStop(i, 1);
                break;

            case "yesNoBox":
              if (item.properties[table[i].propertyName])  widget.setCellText(i, 1, "Да");
              else widget.setCellText(i, 1, "Нет");
              break;

            default:
               widget.setCellText(i, 1, item.properties[table[i].propertyName]);
            }
        }
    }
    widget.setCurrentCell(-1, -1);
}

function savePropertyFromEditor(widget, row)
{
    var table = widget.item.ui().table;
    if (table[row].propertyName in widget.item.properties)
    {
        switch (table[row].widgetType)
        {
//        case "checkBox":
//            widget.item.properties[table[row].propertyName] = widget.getBooleanValueFromCell(row, 1);
//            break;

        case "spinBox":
            widget.item.properties[table[row].propertyName] = widget.cellText(row, 1).replace(",", ".");
            break;

        case "yesNoBox":
          if (widget.cellText(row, 1) === "Да")  widget.item.properties[table[row].propertyName] = true;
          else widget.item.properties[table[row].propertyName] = false;
          break;

        default:
           widget.item.properties[table[row].propertyName] = widget.cellText(row, 1);
        }
    }
}

function savePropertiesFromEditor(widget)
{
    var table = widget.item.ui().table;
    for (var i = 0; i < table.length; i++) savePropertyFromEditor(widget, i);
}

function propEditorCurrentCellChanged(widget, currentRow, currentColumn, previousRow, previousColumn)
{
    var table = widget.item.ui().table;
    if (previousColumn === 1)
    {
        switch (table[previousRow].widgetType)
        {
        case "lineEdit":
            widget.removeLineEdit(previousRow);
            break;

        case "comboBox":
            widget.removeComboBox(previousRow);
            break;

//        case "checkBox":
//            widget.removeCheckBox(previousRow);
//            break;

        case "spinBox":
            widget.removeSpinBox(previousRow);
            break;

        case "yesNoBox":
            widget.removeYesNoBox(previousRow);
            break;
        }
    }

    if (currentColumn === 1)
    {
        switch (table[currentRow].widgetType)
        {
        case "lineEdit":
            widget.setLineEdit(widget.cellText(currentRow, currentColumn));
            lineEdit.textChanged.connect(function(currentText){widget.item.properties[table[currentRow].propertyName] = currentText});
            break;

        case "comboBox":
            widget.setComboBox(widget.cellText(currentRow, currentColumn), table[currentRow].valueList(widget.item));
            comboBox.currentTextChanged.connect(function(currentText){widget.item.properties[table[currentRow].propertyName] = currentText});
            break;

//        case "checkBox":
//            widget.setCheckBox();
//            checkBox.toggled.connect(function(checked){widget.item.properties[table[currentRow].propertyName] = checked});
//            break;

        case "spinBox":
            widget.setSpinBox();
            if ("decimals" in table[currentRow]) spinBox.decimals = table[currentRow].decimals;
            if ("maximum" in table[currentRow]) spinBox.maximum = table[currentRow].maximum;
            if ("minimum" in table[currentRow]) spinBox.minimum = table[currentRow].minimum;
            if ("singleStep" in table[currentRow]) spinBox.singleStep = table[currentRow].singleStep;
            spinBox.value = Number(widget.cellText(currentRow, currentColumn).replace(",", "."));
            spinBox.valueChanged.connect(
                        function(currentValue)
                        {
                            widget.item.properties[table[currentRow].propertyName] = currentValue.replace(",", ".");
                        });
            break;

        case "yesNoBox":
            widget.setYesNoBox(widget.item.properties[table[currentRow].propertyName]);
            comboBox.currentTextChanged.connect(
                        function(currentText)
                        {
                            if (currentText === "Да") widget.item.properties[table[currentRow].propertyName] = true;
                            else widget.item.properties[table[currentRow].propertyName] = false;
                        }
                        );
            break;

        }
    }
}

//---Работа с проектом----------------------------------------------------------------------------------------------

function createNewProject()
{
    projectList.push(Project.createNew());
    currentProject = projectList[projectList.length - 1];
    readPropertiesToEditor(generalProjectDataWidget, currentProject);
}

function saveProject()
{
    savePropertiesFromEditor(generalProjectDataWidget);
    var fileName = currentProject.projectFileName;
    if (fileName !== "")
    {
        projectFile.save(fileName, JSON.stringify(currentProject, "", 4));
        return;
    }

    fileName = projectFile.getSaveFileName();
    if (fileName !== "")
    {
        currentProject.projectFileName = fileName;
        projectFile.save(fileName, JSON.stringify(currentProject, "", 4));
    }

}

function saveProjectAs()
{
    savePropertiesFromEditor(generalProjectDataWidget);
    var fileName = projectFile.getSaveFileName();
    if (fileName !== "")
    {
        currentProject.projectFileName = fileName;
        projectFile.save(fileName, JSON.stringify(currentProject, "", 4));
    }
}

function openProject()
{
    var projectInJSON = JSON.parse(projectFile.load());
    projectList.push(Project.createNew());
    currentProject = projectList[projectList.length - 1];
    currentProject.properties = projectInJSON.properties;
    for (var i = 0; i < projectInJSON.sectionList.length; i++)
    {
        currentProject.sectionList.push(Section.createNew());
        currentProject.sectionList[i].properties = projectInJSON.sectionList[i].properties;
    }

    currentSection = currentProject.sectionList[0];
    currentProject.projectFileName = projectInJSON.projectFileName;
    readPropertiesToEditor(generalProjectDataWidget, currentProject);
    readPropertiesToEditor(sectionParamsWidget, currentSection);
}

//---Работа с участком---------------------------------------------------------------------------------------------------

function createNewSection()
{
    if (projectList.length > 0)
    {
        currentProject.sectionList.push(Section.createNew());
        currentProject.currentSectionIndex = currentProject.sectionList.length - 1;
        currentSection = currentProject.sectionList[currentProject.sectionList.length - 1];
        readPropertiesToEditor(sectionParamsWidget, currentSection);
    }
}

//------------------------------------------------------------------------------------------------------------------------

newProjectAction.triggered.connect(createNewProject);
saveProjectAction.triggered.connect(saveProject);
saveProjectAsAction.triggered.connect(saveProjectAs);
openProjectAction.triggered.connect(openProject);
newSectionAction.triggered.connect(createNewSection);
calcSectionParamsAction.triggered.connect(
            function()
            {
                currentSection.calc();
            });

generalProjectDataWidget.currentCellChanged.connect(
            function(currentRow, currentColumn, previousRow, previousColumn)
            {
                propEditorCurrentCellChanged(generalProjectDataWidget, currentRow, currentColumn, previousRow, previousColumn)
            });

sectionParamsWidget.currentCellChanged.connect(
            function(currentRow, currentColumn, previousRow, previousColumn)
            {
                propEditorCurrentCellChanged(sectionParamsWidget, currentRow, currentColumn, previousRow, previousColumn);
            });

