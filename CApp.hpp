#pragma once

/// <summary>
/// Forward references
/// </summary>
/// 
class CRender;
class CEndPoint;
class CPrediction;


class CApp
{
private:
	
public:
	CRender render;
	CEndPoint endpoint;
	CPrediction prediction;
	void Run();


};

