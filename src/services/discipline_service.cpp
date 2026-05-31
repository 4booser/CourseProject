#include "services/discipline_service.h"

#include "repositories/discipline_repository.h"
#include "repositories/workload_repository.h"

namespace services
{
    OperationResult ValidateDiscipline(const models::Discipline& discipline)
    {
        if (discipline.name.empty())
        {
            return OperationResult::Fail("Назва дисциплiни не може бути порожньою.");
        }

        if (discipline.quota == 0)
        {
            return OperationResult::Fail("Кiлькiсть годин дисциплiни повинна бути бiльше 0.");
        }

        return OperationResult::Ok();
    }

    OperationResult CreateDiscipline(models::Discipline& discipline)
    {
        OperationResult validation_result = ValidateDiscipline(discipline);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return SaveDiscipline(discipline);
    }

    OperationResult UpdateDiscipline(unsigned short discipline_id, const models::Discipline& discipline)
    {
        if (!GetDisciplineById(discipline_id).has_value())
        {
            return OperationResult::Fail("Дисциплiну з таким Id не знайдено.");
        }

        OperationResult validation_result = ValidateDiscipline(discipline);
        if (!validation_result.success)
        {
            return validation_result;
        }

        return EditDisciplineById(discipline_id, discipline);
    }

    OperationResult DeleteDiscipline(unsigned short discipline_id)
    {
        if (!GetDisciplineById(discipline_id).has_value())
        {
            return OperationResult::Fail("Дисциплiну з таким Id не знайдено.");
        }

        if (HasWorkloadForDiscipline(discipline_id))
        {
            return OperationResult::Fail("Дисциплiна використовується в навантаженнi.");
        }

        return RemoveDisciplineById(discipline_id);
    }
}
