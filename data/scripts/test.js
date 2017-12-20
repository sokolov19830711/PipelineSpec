function showProperties(object)
{
    var propertyList = "";
    for (key in object)
    {
        propertyList += key;
        propertyList += "\n";
    }
    return propertyList;
}

function closeWidget()
{
    generalProjectDataWidget.close();
}
